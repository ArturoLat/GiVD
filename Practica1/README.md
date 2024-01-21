# RayTracingToy
Pràctica 1 - GiVD 2022-23

## Taula de continguts:
* [Equip](#Equip)
* [Features](#Features)
* [Explicació de la pràctica](#Explicació)
* [Preguntes de la pràctica](#Preguntes)
* [Screenshots de cada fase](#Screenshots)


## Equip
**B03**
* Arturo Latorre
* Zijian Jiang
* Nil Torrelles
* Asier Augusto

## Features
- Fase 0
    - [x] Background amb degradat
        - Arturo + Zijian
    - [x] Color Shading
        - Arturo + Nil (Arreglat error menor, que donaba error amb la Box y el Triangle)
    - [x] Normal Shading
        - Arturo
    - [x] Depth Shading
        - Asier + Zijian
    - [x] Intersecció amb l'escena
        - Arturo
 - Fase 1
    - Creació de nous objectes i interseccions (VIRTUALWORLD) 
        - [x] Hit Box
            - Nil
        - [x] Hit Triangle
            - Zijian + Arturo + Nil (Arreglat el métode de Transformació -> AplicaTG)
        - [x] Hit Malla
            - Arturo + Zijian
    - Creació de nous objectes i interseccions (REALDATA)
        - [x] 5a) Zijian + Asier
        - [x] 5b) Nil + Zijian
        - [x] 5c) Nil
        - [x] 5d) Nil
        
 - Fase 2
    - [x] PAS 1
        - [x] Zijian + Asier
    - [x] PAS 2
        - [x] Blinn-Phong: Zijian + Arturo
        - [x] Phong: Zijian + Arturo
        - [x] Cel-Shading: Nil + Zijian 
    - [x] PAS 3
        - [x] Blinn-PhongShadow: Asier + Arturo
        - [x] NormalShadow: Arturo + Nil (Arreglat error causat amb el fitted Plane)
        - [x] PhongShadow: Arturo
        - [x] CellShadow: Nil
        - [x] ColorShadow: Arturo + Nil (Arreglat error causat amb el fitted Plane)
        - [x] Escena Complexa: Arturo
    - [x] PAS 4: Metal
        - [x] RayTracer: Arturo
        - [x] Metal: Arturo
    - [x] PAS 4: Transparent
        - [X] RayTracer: Nil 
        - [X] Transparent: Nil + Arturo (Arreglat errors)
    - [x] PAS 5: Visualitzation mapping
        - [x] Data0: Arturo

- Parts opcionales: 
  - [x] Cilindres
    Nil (Cilindre sense les bases superior e inferior per una millor observació [Sense les dos elipses], recomanat jugar amb els eixos de la Camara per apreciarlo)
  - [x] Afegir Fitted-Plane com un botó per la main.ui que permet posar un pla, a qualsevol tipus d'escena:
    Nil
  
    
    
## Explicació    
  * **Organització de la pràctica**
    * descriu com us heu organitzat
  
  * **Decisions a destacar**
    * Comenteu les decisions que heu pres 
    
## Preguntes
- Fase 0:
    - B) Quina escena es té carregada? Qui la crea? Quin setup té la classe? Des d’on es crea?
      - Resposta
    - C) Per què es veu aquest degradat? A quin mètode es calcula aquest color?
      - A RayTracer.
    - D) Quin efecte et trobes? Per què? Pots veure com ha arribat el flag de background al teu RayTracer? 
      - Resposta
    - E) En quina variable els trobes?
      - El color els trobes al vec3 color
    - F) I si volguessis canviar els colors del degradat? On els canviaries?
      - Si volguessis canviar els colors del degradat, hauries de canbiar el RGB = (0.5, 0.7, 1.0), pero tambe es pot fer que agafi els colors de la 
        paleta de colors, i es canvia a RayTracer.
    - G) Si prems Trace, no la veuràs, per què? 
      - Perque no esta calcular el hit, i has de modificar per a que en aquestos punts hi hagi un color que sera el del Shading.
    - H) Com hi pots accedir? A quina variable pots aconseguir l’estratègia a cridar? Com es crea aquesta estratègia des del menú?
      - Pots accedir-hi desde el setup, i agafant el color shading que tu volguis aplicar des del menu.
      - Ara mateix solament podem accedir a ColorShadow o ColorShading, pero mes endavant podrem a NormalShading y DepthShading.
      - Aquesta estrategia es crea des del menu que crida al builder, i alla crea el NormalShading del ShadingFactory.
    - I) Com faràs per a crear una nova estratègia de shading?
      - Per crear aquesta nova estrategia s'ha de habilitar el ui desde MainWindow, despres crear el metode en el builder que sera semblant al del
        ColorShading, pero creant NormalShading. Despres modificarem el ShadingFactory per aixi tenir el NormalShading. Y per ultim crearem la classe
        NormalShading (arxius cpp i hh) on cridarem la normal del HitInfo. 
    - J)  Com aconsegueixes que els colors estiguin normalitzats?
      - Amb la funció normalize(), que normalitza el producte normal de dos vectors. 
    - N) Per què veus només una esfera? On està situada a la teva escena? Amb quin radi? Per què? Per què és lila i no de color "kd": [0.7,0.6,0.5] com posa el
         fitxer?
      - Resposta
- Fase 1: 
    - 3A) Quan penses que es millor crear els triangles de la malla?
      - Just al tancar el fitxer, creas els triangles de la mesh, ja que estarà tot llegit
    - 
- Fase 2:
    - 1.2) On afegiries un atribut numSamples que defineixi el nombres de rajos per pixel i aixi controlar aquest fet?
      - Podriem afegir aquest atribut a la classe-> RayTracer com un int, així ens permetria controlar el nombre de raigs generats per a cada píxel.
    - 1.3) Es tracta de fer l'arrel quadrada de cada canal del color just abans de pintar-lo. On faras aquesta correcio?
      - Si es fa just abans de pintar, hauriem de fer la correció a la classe ColorShading.
    - 2.3) Què necessites canviar?
      - S'ha de canviar el metode de com calculem la difosa, ja que no utilitzarem el vector mig, sino el de reflexió.
    - 2.4) Necessites afegir informació en el material?
      - No es necessari afegir cap informació al material, ja que el material no pot ser opac, unicament s'ha de jugar amb els angles de la llum.
    - 3.2) Quina component de la formula de Blinn-Phong s'haura de tenir en compte?
      - Unicament s'ha de tenir en compte la component del vector L, ja que aixi sabras quan hi ha un objecte, i podras crear la sombra. 
    - 4.3) On hauries de llegir-la?
      - La llegim desde el Material a través del fitxer .json.
    - 4.3) Per que si tens el MAX_DEPTH a 1, l'esfera no es veu transparent?
      - Es la variable que s'ocupa de calcular els rajos secundaris, per tant (el nombre max que el programa calcula que un raig pugui seguir rebotant).
        Al establir un Max-Depth baix els rajos es calculen amb meys presició  i per tant l'imatge es menys clara.
    - 4.3) Com et canvia la visualització? Raona el perque?
        -Això pot fer que els objectes semblin més il·luminats i detallats, però també pot fer que la escena sembli menys realista ja que els raigs secundaris que no           intersequen amb res haurien de rebre un color proper a l'objecte que els envolta o al color de fons.
    - 4.3) Raona per què es veuen totes mes clares que les anteriors.
      -Això és degut al fet que s'ometen els efectes de difusió als marges dels objectes i es simplifica la manera en què la llum es reflexa als objectes.
      
    
    

## Screenshots
* **Fase 0**: 

* **Fase 1**: 

* **Fase 2**

    - Pas 2.2) Afegeix els teus resultats pas a pas en el README del teu projecte:
        - [Només component ambient](https://user-images.githubusercontent.com/72517965/227713663-9c22f466-4d90-4069-be9f-946b8517594e.png)
        - [Només component difosa](https://user-images.githubusercontent.com/72517965/227709908-b575eb86-2813-48f2-aa8e-d0429be96623.png)
        - [Només component especular](https://user-images.githubusercontent.com/72517965/227713128-3c4bc30d-501e-4c8c-a11e-aa94dfe97cc7.png)
        - [Les tres junts](https://user-images.githubusercontent.com/72517965/227713739-8f048ecb-c389-4a6f-9369-4e2f4e41f750.png)
        - [Atenuació amb profunditat](https://user-images.githubusercontent.com/72517965/227713760-31417e91-739f-42dd-b879-ed53d8d57d0e.png)
        - [Afegint ambient global](https://user-images.githubusercontent.com/72517965/227713854-62f4b88a-7946-4e36-832c-d02c1168f904.png)
    - Pas 2.3) Fes la captura final per a comparar-la amb el mètode de Blinn-Phong Shading:
        - [Només component ambient](https://user-images.githubusercontent.com/72517965/227714543-d42a4615-f2b6-4bb5-8955-dedae9724a28.png)
        - [Només component difosa](https://user-images.githubusercontent.com/72517965/227714550-514d8b1c-b12d-4591-902f-3047f753cab1.png)
        - [Només component especular](https://user-images.githubusercontent.com/72517965/227714553-b90d0471-0ab9-4ec0-b16d-f9ede8ab2b79.png)
        - [Captura Final](https://user-images.githubusercontent.com/72517965/227714565-fee5ba84-c185-453f-9fe7-6ebb679ae1a9.png)
    - Pas 2.4) Fes captures de pantalles amb els resultats obtinguts.
        - [Cell Shading](https://user-images.githubusercontent.com/72517965/227773926-7d1533f5-c12b-451c-a703-7c7a6c460199.png)
    - Pas 3) Captures de les sombres
        - [BlinnPhongShadow](https://user-images.githubusercontent.com/72517965/227743991-4bfdd5d8-f223-464f-bb5f-12033be485e8.png)
        - [BlinnPhongShadow](https://user-images.githubusercontent.com/72517965/227744003-c6d7e68c-6c28-4269-afe5-7d1abb64e7fa.png)
        - [PhongShadow](https://user-images.githubusercontent.com/72517965/227744041-cc5e924f-8d61-4a1d-83cd-f2c419798590.png)
        - [PhongShadow](https://user-images.githubusercontent.com/72517965/227744055-6ebbf687-7344-43f0-a233-f54b3b6fe970.png)
        - [NormalShadow](https://user-images.githubusercontent.com/72517965/227745023-08092f8d-f3b1-4da8-bce1-4106fdd0720b.png)
        - [NormalShadow](https://user-images.githubusercontent.com/72517965/227745040-36e71f79-3ff0-4c79-a2c1-8cb0af31d3e0.png)
        - [ColorShadow](https://user-images.githubusercontent.com/72517965/227745200-fae345f1-2dd5-432e-845b-659e8a87107b.png)
        - [ColorShadow](https://user-images.githubusercontent.com/72517965/227745204-864ab8f0-d346-4f58-9c93-bc996901738c.png)
        - [CellShadow](https://user-images.githubusercontent.com/72517965/227774062-b33706d2-f93f-4913-85ce-6dab4609f82b.png)
        - [CellShadow](https://user-images.githubusercontent.com/72517965/227774135-dbe7a0f3-ba86-41e5-b364-c462c8fea6ff.png)

    -Pas 4) Capturas del materiasls: (incluim Metal i Transparent) (Metal esquerra) (Transparent dreta)
        -[Metal+TransparentDepth1](https://user-images.githubusercontent.com/72096555/228962562-085ba78c-3884-42b8-aa06-8353a396cdcc.png)
        -[Metal+TransparentDepth2](https://user-images.githubusercontent.com/72096555/228962799-01e015f0-8b79-4ae5-be69-aa9ad12f85db.png)
    
    -Pas 5) FITTED PLANE
        - [Data0.json](https://user-images.githubusercontent.com/72517965/229036870-a8e807b0-6659-4da7-937d-226ababe60c4.png)






* **Opcionals**:


* **Més visualitzacions**:

   * Per totes les imatges, incluiu aqui la imatge obtinguda i els fitxers de dades i de configuració que heu fet servir
