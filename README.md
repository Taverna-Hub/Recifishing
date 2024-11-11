![bannergithub](https://github.com/user-attachments/assets/1cf95da2-e9dc-42ca-9eb1-d24bb58ab999)

<p align="center"><b>Recifishing</b> é um jogo de pesca desenvolvido em C utilizando a raylib, ambientado em pontos turísticos de Pernambuco como Marco Zero, Porto de Galinhas e Fernando de Noronha.</p>

---

# ⚙️ Como rodar:

1º)  Você precisará do GCC, make e git para baixar e compilar a biblioteca:
```
sudo apt install build-essential git
```

2º)  Em seguida, instale as bibliotecas necessárias para áudio, gráficos OpenGL e sistema de janelas X11:
```
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
```

3º)  Baixe o código-fonte do Raylib diretamente do GitHub e entre na pasta:
```
git clone --depth 1 https://github.com/raysan5/raylib.git raylib
cd raylib/src/
```

4º)  Compile a raylib:
```
make PLATFORM=PLATFORM_DESKTOP
```

5º)  Instale a raylib:
```
sudo make install
cd ~
```

6º)  Clone o repositório do jogo:
```
git clone https://github.com/Taverna-Hub/Recifishing.git
cd Recifishing
```

7º)  Compile e rode o jogo:
```
make run
```

<br>
