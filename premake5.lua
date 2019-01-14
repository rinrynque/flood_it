workspace "FloodIt"
   configurations { "Debug", "Release"}

project "FloodIt"
   kind "ConsoleApp"
   language "C"
   targetdir "bin/%{cfg.buildcfg}"

   links { "ncurses" }
   
   files { "src/**.h", "src/**.c" }

   filter "configurations:Debug"
      defines { "DEBUG" }
	  symbols 'On'
	  buildoptions { "-Wall -Wextra" }
	  
   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
   
project "Tests"
   kind "ConsoleApp"
   language "C"
   targetdir "bin/%{cfg.buildcfg}"

   files { "src/**.h", "src/**.c" }
   removefiles { "src/main.c" }
   files { "Cunit/**.c", "Cunit/**.h"}
   
   links { "cunit" }
   links { "ncurses" }
   
   filter "configurations:Debug"
      defines { "DEBUG" }
	  symbols 'On'
	  buildoptions { "-Wall -Wextra" }

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"