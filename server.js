const express = require('express');
const multer = require('multer');
const cors = require('cors');
const { exec } = require('child_process');
const fs = require('fs');
const path = require('path');

const app = express();
const PORT = 3000;

// Enable CORS
app.use(cors());
app.use(express.json());
app.use(express.static('.'));

// Configure file upload
const storage = multer.diskStorage({
    destination: function (req, file, cb) {
        cb(null, 'uploads/');
    },
    filename: function (req, file, cb) {
        cb(null, Date.now() + '-' + file.originalname);
    }
});

const upload = multer({ storage: storage });

// Encode endpoint
app.post('/api/encode', upload.single('file'), (req, res) => {
    const inputFile = req.file.path;
    const outputFile = `outputs/compressed-${Date.now()}.bin`;
    const treeFile = `outputs/tree-${Date.now()}.huf`;
    
    // Call C++ program
    const command = `huffman.exe encode "${inputFile}" "${outputFile}" "${treeFile}"`;
    
    exec(command, (error, stdout, stderr) => {
        if (error) {
            return res.json({ success: false, error: stderr || error.message });
        }
        
        try {
                        console.log(stdout)

            const result = JSON.parse(stdout);
            
            // Store file paths in session (for download)
            global.lastCompressed = outputFile;
            global.lastTree = treeFile;
            
            res.json({ success: true, ...result });
        } catch (e) {
            res.json({ success: false, error: 'Failed to parse results' });
        }
        
        // Cleanup input file
        fs.unlinkSync(inputFile);
    });
});

// Decode endpoint
app.post('/api/decode', upload.fields([
    { name: 'compressed', maxCount: 1 },
    { name: 'tree', maxCount: 1 }
]), (req, res) => {
    const compressedFile = req.files['compressed'][0].path;
    const treeFile = req.files['tree'][0].path;
    const outputFile = `outputs/decompressed-${Date.now()}.txt`;
    
    // Call C++ program
    const command = `huffman.exe decode "${compressedFile}" "${treeFile}" "${outputFile}"`;
    
    exec(command, (error, stdout, stderr) => {
        if (error) {
            return res.json({ success: false, error: stderr || error.message });
        }
        
        try {
            console.log(stdout)
            const result = JSON.parse(stdout);
            
            // Store file path for download
            global.lastDecompressed = outputFile;
            
            res.json({ success: true, ...result });
        } catch (e) {
            res.json({ success: false, error: 'Failed to parse results' });
        }
        
        // Cleanup input files
        fs.unlinkSync(compressedFile);
        fs.unlinkSync(treeFile);
    });
});

// Download endpoints
app.get('/api/download/compressed', (req, res) => {
    if (global.lastCompressed) {
        res.download(global.lastCompressed);
    } else {
        res.status(404).send('File not found');
    }
});

app.get('/api/download/tree', (req, res) => {
    if (global.lastTree) {
        res.download(global.lastTree);
    } else {
        res.status(404).send('File not found');
    }
});

app.get('/api/download/decompressed', (req, res) => {
    if (global.lastDecompressed) {
        res.download(global.lastDecompressed);
    } else {
        res.status(404).send('File not found');
    }
});

app.listen(PORT, () => {
    console.log(`🚀 Server running at http://localhost:${PORT}`);
    console.log(`📁 Upload folder: ${path.resolve('uploads')}`);
    console.log(`📁 Output folder: ${path.resolve('outputs')}`);
});