# Отчет по лабораторной работе №6: 

## Выполнила: Князева Таня ИУ8-22
## Репозиторий lab06: https://github.com/tananaa/lab06
## Почта: tanyaknz07@gmail.com


## 1. Настройка репозитория

export GITHUB_USERNAME=tananaa
export GITHUB_EMAIL=tanyaknz07@gmail.com

cd ~/${GITHUB_USERNAME}/workspace
git clone https://github.com/${GITHUB_USERNAME}/lab05 lab06
cd lab06
git remote remove origin
git remote add origin https://github.com/${GITHUB_USERNAME}/lab06.git


## 2. Версионирование проекта

sed -i '/project(lab05)/a\
set(PRINT_VERSION_MAJOR 0)\
set(PRINT_VERSION_MINOR 1)\
set(PRINT_VERSION_PATCH 0)\
set(PRINT_VERSION_TWEAK 0)\
set(PRINT_VERSION ${PRINT_VERSION_MAJOR}.${PRINT_VERSION_MINOR}.${PRINT_VERSION_PATCH}.${PRINT_VERSION_TWEAK})\
set(PRINT_VERSION_STRING "v${PRINT_VERSION}")
' CMakeLists.txt



## 3. Создание файлов метаданных

echo "Static C++ library for printing" > DESCRIPTION

export DATE="`LANG=en_US date +'%a %b %d %Y'`"
cat > ChangeLog.md <<EOF
* ${DATE} tananaa <tanyaknz07@gmail.com> 0.1.0.0
- Initial RPM release
EOF

echo "MIT License" > LICENSE
echo "Copyright (c) 2026 tananaa" >> LICENSE

---

## 4. Конфигурация CPack

cat > CPackConfig.cmake << 'EOF'
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_CONTACT tanyaknz07@gmail.com)
set(CPACK_PACKAGE_VERSION_MAJOR ${PRINT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PRINT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PRINT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION_TWEAK ${PRINT_VERSION_TWEAK})
set(CPACK_PACKAGE_VERSION ${PRINT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/DESCRIPTION)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "static C++ library for printing")

set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README.md)

set(CPACK_RPM_PACKAGE_NAME "print-devel")
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_GROUP "print")
set(CPACK_RPM_CHANGELOG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/ChangeLog.md)
set(CPACK_RPM_PACKAGE_RELEASE 1)

set(CPACK_DEBIAN_PACKAGE_NAME "libprint-dev")
set(CPACK_DEBIAN_PACKAGE_PREDEPENDS "cmake >= 3.0")
set(CPACK_DEBIAN_PACKAGE_RELEASE 1)

include(CPack)
EOF

echo "include(CPackConfig.cmake)" >> CMakeLists.txt

sed -i 's/lab05/lab06/g' README.md



## 5. Локальная сборка и пакетирование

rm -rf _build
cmake -H. -B_build
cmake --build _build
cd _build
cpack -G "TGZ"
cpack -G "DEB"
cd ..

mkdir artifacts
mv _build/*.tar.gz _build/*.deb artifacts/

ls -la artifacts/

Вывод:
-rw-r--r-- lab05-0.1.0.0-Linux.deb
-rw-r--r-- lab05-0.1.0.0-Linux.tar.gz



## 6. Настройка GitHub Actions

mkdir -p .github/workflows

cat > .github/workflows/release.yml << 'EOF'
name: Release

on:
  push:
    tags:
      - 'v*'

permissions:
  contents: write

jobs:
  build_packages:
    runs-on: ubuntu-latest

    steps:
    - name: Checkout code
      uses: actions/checkout@v4

    - name: Install dependencies
      run: |
        sudo apt-get update
        sudo apt-get install -y cmake build-essential

    - name: Configure CMake
      run: cmake -H. -B_build -DCPACK_GENERATOR="TGZ;DEB"

    - name: Build Package
      run: cmake --build _build --target package

    - name: Create GitHub Release
      uses: softprops/action-gh-release@v2
      with:
        files: |
          _build/*.tar.gz
          _build/*.deb
      env:
        GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
EOF



## 7. Отправка на GitHub и создание релизов

git add .
git commit -m "added cpack config"
git push origin main

git tag v0.1.0.0
git push origin main --tags

git add LICENSE
git commit -m "add LICENSE"
git push origin main

git tag v0.1.0.1
git push origin main --tags

git tag v0.1.0.2
git push origin main --tags

git add .github/workflows/release.yml
git commit -m "fix release workflow permissions"
git push origin main

git tag v0.1.0.3
git push origin main --tags


