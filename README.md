[![CMake](https://github.com/CandasKat/http_curl_wrapper/actions/workflows/msvc.yml/badge.svg)](https://github.com/CandasKat/http_curl_wrapper/actions/workflows/msvc.yml)

I recommend to use Clion for compile the project.

For install compilers:

```bash
sudo apt install cmake gcc g++
```

For install cURL:

```bash
sudo apt install curl
sudo apt install libssl-dev libcurl4-openssl-dev
```


For Windows:
I recommend to use Visual Studio for compile the project, and you can use vcpkg for install the dependencies.

For install vcpkg:

```bash
git clone https://github.com/microsoft/vcpkg.git
.\vcpkg\bootstrap-vcpkg.bat
```


For install Curl:

```bash
.\vcpkg\vcpkg install curl:x64-windows
.\vcpkg\vcpkg integrate install
```


For install Google Test:

```bash
.\vcpkg\vcpkg install gtest:x64-windows
```

And you can use the CMakeLists.txt file for compile the project.
For execute the project you need to use http_curl_wrapper_test.exe (tst\http_curl_wrapper_tst.exe)._
