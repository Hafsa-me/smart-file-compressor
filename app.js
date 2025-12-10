let encodeFileData = null;
let compressedFileData = null;
let treeFileData = null;

function showTab(tabName) {
    // Hide all tabs
    document.querySelectorAll('.tab-content').forEach(tab => {
        tab.classList.remove('active');
    });
    
    document.querySelectorAll('.tab-btn').forEach(btn => {
        btn.classList.remove('active');
    });
    
    // Show selected tab
    document.getElementById(tabName + '-tab').classList.add('active');
    event.target.classList.add('active');
    
    // Hide results
    hideResults();
}

function handleEncodeFile(event) {
    const file = event.target.files[0];
    if (file) {
        encodeFileData = file;
        document.getElementById('encode-filename').textContent = `Selected: ${file.name}`;
    }
}

function handleCompressedFile(event) {
    const file = event.target.files[0];
    if (file) {
        compressedFileData = file;
        document.getElementById('compressed-filename').textContent = `Selected: ${file.name}`;
    }
}

function handleTreeFile(event) {
    const file = event.target.files[0];
    if (file) {
        treeFileData = file;
        document.getElementById('tree-filename').textContent = `Selected: ${file.name}`;
    }
}

async function encodeFile() {
    if (!encodeFileData) {
        showError('Please select a file to compress!');
        return;
    }
    
    showLoading();
    hideError();
    
    const formData = new FormData();
    formData.append('file', encodeFileData);
    formData.append('action', 'encode');
    
    try {
        const response = await fetch('http://localhost:3000/api/encode', {
            method: 'POST',
            body: formData
        });
        
        const result = await response.json();
        
        if (result.success) {
            displayEncodeResults(result);
        } else {
            showError(result.error || 'Encoding failed!');
        }
    } catch (error) {
        showError('Connection error: ' + error.message);
    } finally {
        hideLoading();
    }
}

async function decodeFile() {
    if (!compressedFileData || !treeFileData) {
        showError('Please select both compressed and tree files!');
        return;
    }
    
    showLoading();
    hideError();
    
    const formData = new FormData();
    formData.append('compressed', compressedFileData);
    formData.append('tree', treeFileData);
    formData.append('action', 'decode');
    
    try {
        const response = await fetch('http://localhost:3000/api/decode', {
            method: 'POST',
            body: formData
        });
        
        const result = await response.json();
        
        if (result.success) {
            displayDecodeResults(result);
        } else {
            showError(result.error || 'Decoding failed!');
        }
    } catch (error) {
        showError('Connection error: ' + error.message);
    } finally {
        hideLoading();
    }
}

function displayEncodeResults(result) {
    document.getElementById('original-size').textContent = result.originalSize + ' bytes';
    document.getElementById('compressed-size').textContent = result.compressedSize + ' bytes';
    document.getElementById('compression-ratio').textContent = result.compressionRatio + '%';
    
    // Display frequency table
    const tableHTML = `
        <table>
            <thead>
                <tr>
                    <th>Character</th>
                    <th>Frequency</th>
                    <th>Huffman Code</th>
                </tr>
            </thead>
            <tbody>
                ${result.frequencies.map(item => `
                    <tr>
                        <td>${escapeHtml(item.char)}</td>
                        <td>${item.freq}</td>
                        <td>${item.code}</td>
                    </tr>
                `).join('')}
            </tbody>
        </table>
    `;
    
    document.getElementById('frequency-table').innerHTML = tableHTML;
    document.getElementById('encode-result').classList.remove('hidden');
}

function displayDecodeResults(result) {
    document.getElementById('decompressed-size').textContent = result.decompressedSize + ' bytes';
    document.getElementById('decode-result').classList.remove('hidden');
}

async function downloadFile(type) {
    let endpoint = '';
    let filename = '';
    
    switch(type) {
        case 'compressed':
            endpoint = '/api/download/compressed';
            filename = 'compressed.bin';
            break;
        case 'tree':
            endpoint = '/api/download/tree';
            filename = 'tree.huf';
            break;
        case 'decompressed':
            endpoint = '/api/download/decompressed';
            filename = 'decompressed.txt';
            break;
    }
    
    try {
        const response = await fetch('http://localhost:3000' + endpoint);
        const blob = await response.blob();
        
        const url = window.URL.createObjectURL(blob);
        const a = document.createElement('a');
        a.href = url;
        a.download = filename;
        document.body.appendChild(a);
        a.click();
        window.URL.revokeObjectURL(url);
        document.body.removeChild(a);
    } catch (error) {
        showError('Download failed: ' + error.message);
    }
}

function showLoading() {
    document.getElementById('loading').classList.remove('hidden');
}

function hideLoading() {
    document.getElementById('loading').classList.add('hidden');
}

function showError(message) {
    const errorDiv = document.getElementById('error-message');
    errorDiv.textContent = message;
    errorDiv.classList.remove('hidden');
    
    setTimeout(() => {
        errorDiv.classList.add('hidden');
    }, 5000);
}

function hideError() {
    document.getElementById('error-message').classList.add('hidden');
}

function hideResults() {
    document.getElementById('encode-result').classList.add('hidden');
    document.getElementById('decode-result').classList.add('hidden');
}

function escapeHtml(text) {
    const map = {
        '&': '&amp;',
        '<': '&lt;',
        '>': '&gt;',
        '"': '&quot;',
        "'": '&#039;',
        ' ': 'SPACE',
        '\n': 'NEWLINE',
        '\t': 'TAB'
    };
    return map[text] || text;
}