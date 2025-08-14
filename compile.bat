@echo off
REM Script'in bulunduðu klasöre geç
cd /d "%~dp0"

REM Vertex shader'ý derle
C:\VulkanSDK\1.4.313.2\Bin\glslc.exe Shaders\simple_shader.vert -o Shaders\simple_shader.vert.spv

REM Fragment shader'ý derle
C:\VulkanSDK\1.4.313.2\Bin\glslc.exe Shaders\simple_shader.frag -o Shaders\simple_shader.frag.spv

pause