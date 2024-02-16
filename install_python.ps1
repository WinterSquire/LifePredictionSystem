# Download Python
$URL_ZIP = "https://www.python.org/ftp/python/3.8.0/python-3.8.0-embed-amd64.zip"
$ZIP_PATH = "$env:TEMP\python-3.8.0-embed-amd64.zip"
$OUTPUT_PATH = "./python"

if (-not (Test-Path $ZIP_PATH)) {
    Invoke-WebRequest -Uri $URL_ZIP -OutFile $ZIP_PATH
}

# Extract Python
if (-not (Test-Path $OUTPUT_PATH)) {
    New-Item -ItemType Directory -Path $OUTPUT_PATH
}

if (-not (Test-Path $OUTPUT_PATH/python38.dll)) {
    7z x $ZIP_PATH -o"./python"
    Copy-Item $OUTPUT_PATH/python38.dll ./
}

cd $OUTPUT_PATH

# Get pip 
$URL_GET_PIP = "https://bootstrap.pypa.io/get-pip.py"
$FILE_GET_PIP = "get-pip.py";

if (-not (Test-Path $FILE_GET_PIP)) {
    Invoke-WebRequest -Uri $URL_GET_PIP -OutFile $FILE_GET_PIP
}

./python $FILE_GET_PIP

# Site.Main()
Remove-Item "python38._pth"
"python38.zip" | Add-Content -Path "python38._pth"
"." | Add-Content -Path "python38._pth"
"import site" | Add-Content -Path "python38._pth"

# Install Package
./python -m pip install numpy
./python -m pip install scikit-learn
./python -m pip install tensorflow

if (Test-Path $ZIP_PATH) {
    Remove-Item $ZIP_PATH
}

cd ..

echo "Done!"
