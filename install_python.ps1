# Download Python
$PYTHON_VERSION = "3.9.13"
$PYTHON_VER = "39"
$URL_ZIP = "https://www.python.org/ftp/python/$PYTHON_VERSION/python-$PYTHON_VERSION-embed-amd64.zip"
$ZIP_PATH = "$env:TEMP\python-$PYTHON_VERSION-embed-amd64.zip"
$OUTPUT_PATH = "./python"

if (-not (Test-Path $ZIP_PATH)) {
    Invoke-WebRequest -Uri $URL_ZIP -OutFile $ZIP_PATH
}

# Extract Python
if (-not (Test-Path $OUTPUT_PATH)) {
    New-Item -ItemType Directory -Path $OUTPUT_PATH
}

if (-not (Test-Path "$OUTPUT_PATH/python$PYTHON_VER.dll")) {
    7z x $ZIP_PATH -o"./python"
    Copy-Item "$OUTPUT_PATH/python$PYTHON_VER.dll" ./
}

cd $OUTPUT_PATH

# Get pip 
$URL_GET_PIP = "https://bootstrap.pypa.io/get-pip.py"
$FILE_GET_PIP = "../script/get-pip.py";

if (-not (Test-Path $FILE_GET_PIP)) {
    Invoke-WebRequest -Uri $URL_GET_PIP -OutFile $FILE_GET_PIP
}

./python $FILE_GET_PIP

# Site.Main()
Remove-Item "python$PYTHON_VER._pth"
"python$PYTHON_VER.zip" | Add-Content -Path "python$PYTHON_VER._pth"
"." | Add-Content -Path "python$PYTHON_VER._pth"
"import site" | Add-Content -Path "python$PYTHON_VER._pth"

# Install Package
$mirror = "https://pypi.tuna.tsinghua.edu.cn/simple"

./python -m pip install numpy -i $mirror
./python -m pip install scikit-learn -i $mirror
./python -m pip install tensorflow -i $mirror

#if (Test-Path $ZIP_PATH) {
#    Remove-Item $ZIP_PATH
#}

cd ..

echo "Done!"
