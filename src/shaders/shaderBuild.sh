#!/bin/bash

NEWHEADER=0

if [ "shader.vert" -nt "vert.spv" ]
then
	echo "Compliling vertex shader"
	NEWHEADER=1

	glslangValidator -V shader.vert
fi
if [ "shader.frag" -nt "frag.spv" ]
then
	echo "Compliling fragment shader"
	NEWHEADER=1

	glslangValidator -V shader.frag
fi

if ! [ -f "CompiledShaders.h" ]
then
	NEWHEADER=1
fi

if [ "$NEWHEADER" == "1" ]
then
	echo "Building Shader Header"

	echo "/*" > CompiledShaders.h 
	echo " * Pre-compiled and stored SPIR-V shader binaries" >> CompiledShaders.h
	echo " * DO NOT MODIFY" >> CompiledShaders.h
	echo " * Built at: $(date +'%Y-%m-%dT%T')" >> CompiledShaders.h
	echo " */" >> CompiledShaders.h 
	echo " " >> CompiledShaders.h 

	echo "// Vertex Shader" >> CompiledShaders.h 
	xxd -i vert.spv >> CompiledShaders.h
	echo " " >> CompiledShaders.h 
	echo "// Fragment Shader" >> CompiledShaders.h 
	xxd -i frag.spv >> CompiledShaders.h
fi
