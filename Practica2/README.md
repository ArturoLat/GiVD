# ZBufferToy
Codi de la Pràctica 2 de GiVD: ZBufferToy 2022-23

## Taula de continguts

* [Equip](#Equip)
* [Abstract](#Abstract)
* [Features](#Features)
* [Extensions addicionals](#Extensions)
* [Memòria](#Memòria)
* [Fotografies](#Fotografies)


## Equip

**B03**
* Arturo Latorre
* Zijian Jiang
* Nil Torrelles
* Asier Augusto
    
## Abstract

Petit resum de fins on heu arribat a fer

## Features

A continuació s'indica quines parts s'han fet i qui les ha implementat
- Fase 1
    - Lights
        - [x] Ambient Global [Nil] + [Zijian] + [Asier]
        - [x] Puntual [Nil] 
        - [x] Direccional [Nil] 
        - [x] Spotlight [Nil] 
        - [x] Conexió GPU  + vshader1.glsl implementation [Nil]
        - [x] Arreglament de Lights [Asier + Arturo]
    - Materials: 
       - [x] Inici Materials [Nil + Asier]
       - [x] Pas a la GPU [Arturo]
       - [x] Lectura de fitxers .json: [Arturo]
    - Shading
        - [x] Color: [Arturo]
            - [x] Conexió GPU: [Arturo]
        - [x] Normal: [Arturo]
            - [x] Conexió GPU: [Arturo]
        - [x] Depth: [Arturo]
            - [x] Conexió GPU: [Arturo]
        - [x] Phong-Gouraud :  [Arturo]
            - [x] Conexió GPU: [Nil]
        - [x] Phong-Phong:  [Arturo]
            - [x] Conexió GPU: [Nil]
        - [x] BlinnPhong-Gouraud : [Arturo]
            - [x] Conexió GPU: [Nil]
        - [x] BlinnPhong-Phong :  [Arturo]
            - [x] Conexió GPU: [Arturo + Nil]
        - [x] Cel-shading :  [Nil]
            - [x] Conexió GPU: [Nil]
    - Textures
        - [ ] Textura com material en un objecte [Zijian] IN PROGRESS
        - [ ] Textura al pla base [Zijian] IN PROGRESS
    - Adaptació a la lectura de fitxers de dades
        - [ ] Escenes virtuals 
        - [ ] SetUp
        - [ ] Escenes de dades 

- Fase 2 
    - [ ] Visió nocturn IN PROGRESS
    - [x] La Tempesta de Fornite: [Asier]
        - [x] Arreglament Fortnite: [Arturo]
    - [ ] Èmfasi de siluetes 
    - [ ] Mapping indirecte de textures
    - [ ] Animacions amb dades temporals
    - [ ] Normal mapping 
    - [ ] Entorn amb textures
    - [ ] Reflexions
    - [ ] Transparències via objectes: 
    - [ ] Transparències via environmental mapping


## Extensions


## Memòria

- Fase 1
    -   Decideix el moment en el que cal passar la llum ambient global a la GPU (al initializeGL? Al updateGL? En crear un objecte? ). 
        -   Pasarem la llum ambient global, al initialieGL (metode de la classe GlWidget), es a dir, al inicialitzar l'aplicació. Ja que volem que la llum ambient global,  sigui estàtica, i no es modifiqui durant el trancurs de l'execució.
    -   Què contindrà el "struct" de la GPU? Com l’estructurareu?
        -   El struct de cada llum ha de tenir les variables de cada llum, per exemple:
            -   DirectionalLight: Ia, Id, Is, dir
            -   SpotLight: Ia, Id, Is, abc, dir, pos, angle
            -   PointLight: Ia, Id, Is, abc, pos
        -   L'estructurarem d'aquesta manera, i com el toGPU de GPULight es la mare dels tres fills, a cada tipus de GPU de la llum omplirem cada struct a la GPU.
    -   Ara es crea una llum puntual al initializeGL() de la classe GLWidget, quan l’hauries de passar a la GPU? A l’inici de tot? Cada vegada que es visualitza l’escena? 
        -   Cada vegada que es visualitza l'escena, es pot incloure a update o cada vegada que trucas a un shader, fer una trucada a lightsTOGPU(). 
    -   Des d’on es cridarà aquest mètode?
        -   Aquest metode es crida desde GPUScene, on per a cada objecte, cridem al toGPU.
    -   Si vols utilitzar diferents shaders en temps d'execució raona on s'inicialitzaran els shaders i com controlar quin shader s'usa? Cal tornar a passar l'escena a la GPU quan es canvia de shader?
        -   Nosaltres els controlem amb el pasarShader on initicialitzem primerament aquest amb el colorShading, i despres d'inicialitzar tots els shaders, a cada activar el shader, posem aquest pasarShader al valor que hagem possat al program a initShadersToGPU. Cada vegada que canviem de shader s'ha de fer el link, bind, cridar les llums de nou i fer un updateGL.
    -   Cal tenir un parell de vèrtex-fragment shader? O dos?
        -   Hem de tenir un vertex-fragment shader per cadascun, un per Blinn-Phong i un per Phong.
    -   Quina diferència hi ha amb el Gouraud-shading? On l'has de codificar? Necessites uns nous vertex-shader i fragment-shader?
        -   La diferencia es que per Phong es calcula al fragment, en canvi, per Gouraud es calcula al vertex. Al igual que l'anterior, necesitem un per cadascun, un per Phong Phong, i un altre per Phong Blinn-Phong.
    -   On s'implementarà el càlcul del color per a tenir més trencament entre las games de colors? Necessites uns nous vertex-shader i fragment-shader?
        -   Per aconseguir un major trencament de les diferents gamas de colors, es pot utilitzar una funció de mapeig no lineal per aplicar una transformació als valors de color.
        -   Implementar aquesta funció requereix codificar nous vertex-shader i fragment-shader que permetin l'ús d'aquesta funció de mapeig no lineal als valors de color.
        
## Fotografies
-   [ColorShading](https://github.com/GiVD2022/p2-zbuffertoy-b03/assets/72517965/2f0a62e8-087d-48ea-9e4d-98f665fa4cbf)
-   [NormalShading](https://github.com/GiVD2022/p2-zbuffertoy-b03/assets/72517965/d112f997-9bc7-4e5d-82c1-85c3035a6dd9)
-   [DepthShading](https://github.com/GiVD2022/p2-zbuffertoy-b03/assets/72517965/b2f31da9-8c0b-4edc-974d-f6d6b7b67685)
-   [Gouraud Phong](https://github.com/GiVD2022/p2-zbuffertoy-b03/assets/72517965/ccbdeb94-22f7-41a0-a707-472d7a2a87d9)
-   [Phong Phong](https://github.com/GiVD2022/p2-zbuffertoy-b03/assets/72517965/0cb5bd2e-a30f-4d47-bc40-326c6ecc48d9)
-   [Gouraud Blinn-Phong](https://github.com/GiVD2022/p2-zbuffertoy-b03/assets/72517965/bb73a792-2833-4996-b207-885b35e8233c)
-   [Phong Blinn-Phong](https://github.com/GiVD2022/p2-zbuffertoy-b03/assets/72517965/312b0860-d450-4cd2-86ff-c35ef13b68fe)
-   [Toon](https://github.com/GiVD2022/p2-zbuffertoy-b03/assets/72517965/c38b836a-3e1a-45ff-ac36-9ca87a5850c2)
-   [Fortnite Storm](https://github.com/GiVD2022/p2-zbuffertoy-b03/assets/72517965/1462c658-7b7c-4b95-9e6e-1ee53c693213)





