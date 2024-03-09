# =============Install Python=============
$PYTHON_VERSION = "3.9.13"
$PYTHON_VER = "39"
$URL_ZIP = "https://www.python.org/ftp/python/$PYTHON_VERSION/python-$PYTHON_VERSION-embed-amd64.zip"
$ZIP_PATH = "$env:TEMP\python-$PYTHON_VERSION-embed-amd64.zip"
$OUTPUT_PATH = "./python"

# Download Python
if (-not (Test-Path $ZIP_PATH)) {
    Invoke-WebRequest -Uri $URL_ZIP -OutFile $ZIP_PATH
}

# Test Path
if (-not (Test-Path $OUTPUT_PATH)) {
    New-Item -ItemType Directory -Path $OUTPUT_PATH
}

# Extract Python
Expand-Archive -LiteralPath $ZIP_PATH -DestinationPath "./python"

# Copy DLL
Copy-Item "$OUTPUT_PATH/python$PYTHON_VER.dll" ./

# =============Install pip=============
$URL_GET_PIP = "https://bootstrap.pypa.io/get-pip.py"
$FILE_GET_PIP = "$OUTPUT_PATH\get-pip.py";

# Download get-pip.py
if (-not (Test-Path $FILE_GET_PIP)) {
    Invoke-WebRequest -Uri $URL_GET_PIP -OutFile $FILE_GET_PIP
}

# Execute get-pip.py
./$OUTPUT_PATH/python $FILE_GET_PIP

# Update Site.Main()
"import site" | Add-Content -Path "$OUTPUT_PATH\python$PYTHON_VER._pth"
