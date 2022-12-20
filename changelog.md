# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Changed


## [1.5.259 - 2022-12-20]

### Added

- The software version is now displayed in the statusbar
- New about box displaying embedded libraries versions

### Changed

- Moving from MySQL 5.6.51 to MariaDB 10.6.10
- bumping GDAL to 3.5.2
- bumping gtest to 1.12.1
- Using SVG icons instead of bitmaps for the toolbar
- Export button is now working as expected (see #2)
- Using new application logo (SVG too).

### Removed

- Removing MySQL logo from the main UI


## [1.4.225 - 2022-04-10]

### Added

- Conan-based dependency management (www.conan.io)
- CI/CD using Github actions
- a changelog file
- build instructions 

### Changed

- migration of unit tests in Google Test
- a lot of code cleaning
- Removing old Cmake files
- MySQL updated to version 5.6.51
- updating the readme file

### Fixed

