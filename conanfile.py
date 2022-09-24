from conans import ConanFile, CMake
import os


class ToolbasView(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = [
        "wxwidgets/3.2.1@terranum-conan+wxwidgets/stable",
        "mariadb/10.6.10@terranum-conan+mariadb/stable",
        "gdal/3.5.1@terranum-conan+gdal/stable",
        "libtiff/4.4.0",
        "libdeflate/1.12",
        #"geos/3.10.2",
        #"proj/9.0.0",
        #"libcurl/7.80.0",
        #"zlib/1.2.12"
    ]

    options = {"unit_test": [True, False]}
    default_options = {"unit_test": False}

    generators = "cmake", "gcc", "txt"

    def requirements(self):
        if self.options.unit_test:
            self.requires("gtest/cci.20210126")

    def configure(self):
        self.options["gdal"].with_curl = True # for xml support
        self.options["gdal"].shared = True

        # this isn't needed anymore with wxWidgets 3.2.1
        # if self.settings.os == "Linux":
        #    self.options["wxwidgets"].webview = False  # webview control isn't available on linux.

    def imports(self):
        # copy libraries
        self.copy("*.dll", dst="bin", src="bin")  # From bin to bin
        self.copy("*.dylib", dst="bin", src="lib")
        if self.settings.os == "Linux":
            self.copy("*.so*", dst="bin", src="lib")

        # copy errmsg.sys on different places
        if self.settings.os == "Windows" or self.settings.os == "Linux":
            self.copy("errmsg.sys", dst="bin/mysql", src="share/english")
        if self.settings.os == "Macos":
            self.copy("errmsg.sys", dst="bin/ToolBasView.app/Contents/mysql", src="share/english")
            if self.options.unit_test:
                self.copy("errmsg.sys", dst="mysql", src="share/english")

        # copy proj library datum
        if self.settings.os == "Windows" or self.settings.os == "Linux":
            self.copy("*", dst="bin", src="res", root_package="proj")
        if self.settings.os == "Macos":
            self.copy("*", dst="bin/ToolBasView.app/Contents/share/proj", src="res", root_package="proj")

    def build(self):
        cmake = CMake(self)
        if self.options.unit_test:
            cmake.definitions["USE_UNITTEST"] = "ON"
        cmake.configure()
        cmake.build()
        if self.settings.os == "Macos":
            cmake.install()
