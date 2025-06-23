from conans import ConanFile, CMake
import os


class ToolbasView(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = [
        "wxwidgets/3.3.0@terranum-conan+wxwidgets/stable",
        "mariadb/10.6.22@terranum-conan+mariadb/stable",
        "gdal/3.10.3@terranum-conan+gdal/stable",
        "libtiff/4.7.0",
    ]

    options = {"unit_test": [True, False]}
    default_options = {"unit_test": False}

    generators = "cmake", "gcc", "txt"

    def requirements(self):
        if self.options.unit_test:
            self.requires("gtest/1.15.0")

    def configure(self):
        self.options["gdal"].with_curl = True # for xml support
        self.options["gdal"].shared = True

        if self.settings.os == "Linux":
            self.options["wxwidgets"].png = "system"
            self.options['gdal'].with_png = False # to avoid static linking of libpng

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
