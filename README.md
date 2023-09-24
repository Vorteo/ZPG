# ZPG
Projekt, jednoduchý herní engine

### Project Properties -> C/C++ General/ Add. include. directories:
  
  ..\Libs\glfw-3.3.8.bin.WIN32\glfw-3.3.8.bin.WIN32\include
  
  ..\Libs\glew-2.1.0-win32\glew-2.1.0\include
  
  ..\Libs\glm-master\glm-master
  
   ..\Libs\soil\include
   
   ..\Libs\assimp\include
  
  
  ### Linker / General / Add. Library directories:
  
  ..\Libs\glfw-3.3.8.bin.WIN32\glfw-3.3.8.bin.WIN32\lib-vc2022
  
  ..\Libs\glew-2.1.0-win32\glew-2.1.0\lib\Release\Win32
  
  ..\Libs\soil\lib
  
  ..\Libs\assimp\lib\Win32\v141\Release
  
 ### Linker / Input / Add dep.: 
  
  opengl32.lib
  
  glu32.lib
  
  glfw3.lib
  
  glew32.lib
  
  SOIL.lib
  
  assimp-vc140-mt.lib
  
  - po prvnim buildu pridat do debug slozky glew32.dll a  assimp-vc140-mt.dll
