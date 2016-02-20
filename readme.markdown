Xadribol
=====

Um jogo

Como rodar
-----

- Baixe o Code::Blocks
- Baixe o CMake
- Baixe o SFML 2.3.2 (sources)
- Siga [este guia](http://www.sfml-dev.org/tutorials/2.3/compile-with-cmake.php)
- Ou, em vez de seguir o guia oficial, siga o meu (abaixo)
- No Code::Blocks, em Settings -> Compiler options, marque "Have g++ follow the C++11 ISO [...]"
- Agora, se tudo der certo, "Build and run" roda o projeto direitinho

Meu guia para compilar o SFML
-----
- Crie uma pasta "build" dentro da pasta do SFML que possui "CMakeLists.txt"
- Rode o CMake
- Em "Where is the source code", coloque a pasta do SFML que possui "CMakeLists.txt"
- Em "Where to build the binaries", coloque a pasta "build" criada no primeiro passo
- Clique em "Configure"
- Selecione "Code::Blocks MinGW Makefiles" ou algo parecido
- Clique em "Generate"
- Pronto!