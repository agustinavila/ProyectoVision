# Proyecto Vision

Proyecto final para las materias "Vision Artificial" y "Complementos de Informatica"
El proyecto consiste en un programa capaz de obtener imagenes de distintos medios, detectar caras y analizar su simetria. Ademas, deberia ser capaz de generar reportes y mostrar fotogramas claves, donde la asimetria sea maxima o donde se detecte claramente cierta expresion facial (sonrisa, ceño fruncido, levantar cejas, etc). La idea de la implementación está basada en [este paper][1].

## Tabla de contenidos

+ [Desarrollo](#desarrollo)
+ [Clases](#clases)
  + [Clase feeder](#clase-feeder)
    + [Clase VideoFeeder](#clase-videofeeder)
    + [Clase WebcamFeeder](#clase-webcamfeeder)
    + [Clase KinectFeeder](#clase-kinectfeeder)
  + [Clase ExtractorLandmarks](#clase-extractorlandmarks)
  + [Clase normalizadorLandmarks](#clase-normalizadorlandmarks)
  + [Clase AnalizadorSimetria](#clase-analizadorsimetria)

## Desarrollo

El software consistira de varias clases, "concatenadas" entre si utilizando un esquema de observadores.

![Esquema del funcionamiento general](/Diagrama/proyectoVision.png).

En el esquema anterior, las flechas indican "observadores de". Aun no se si esta implementacion es correcta, ya que seria muy propensa a cuellos de botella en caso de que algun paso falle.

El sistema instanciará los objetos necesarios a partir de argumentos pasados al mismo, con las clases concretas necesarias segun el caso. Si no se pasan argumentos, deberia intentar abrir una webcam, y utilizar un archivo de entrenamiento por defecto.

## Argumentos

+ `arg1` : Lo que hacer el arg1
+ `arg2` : Lo que hacer el arg2

## Clases

A continuacion, se detallan las distintas clases base que compondran al sistema.

### Clase Feeder

 Habrá una clase (por ahora llamada feeder, no se si es un nombre claro) encargada de obtener los fotogramas a analizar. De ésta se derivan tres clases (por ahora) que heredan algunos metodos base pero implementados con distintos fines. Las tres clases que heredan de Feeder, serán:

+ VideoFeeder, pensada para trabajar con videos
+ WebcamFeeder, pensada para adquirir fotogramas de una webcam
+ KinectFeeder, pensada para adquirir fotogramas de una kinect utilizando libfreenect2.

Estas clases tendrán métodos para actualizar sus observadores ([FrameLogger](#clase-framelogger) y [ExtractorLandmarks](#clase-extractorlandmarks)).
Además, tendrán un método para obtener fotogramas en un momento determinado(Es decir, usar algun tipo de semaforo para esperar a cuando el extractor se libere, y recien ahi proveerle otro fotograma? Entiendo que el cuello de botella será el extractor de landmarks)

![Ejemplo del Feeder](/Diagrama/feeder.png)

Ejemplo en UML de la clase "feeder"

### Clase FrameLogger

Esta clase estará encargada de registrar los frames provistos por el [Feeder](#clase-feeder), ya que será un observador. Debe tener un metodo de actualizacion que consista en guardar el archivo de imagen en algun lugar en particular, con un nombre que lo identifique unicamente, y que de alguna manera quede linkeado a una "base de datos" (Me falta definir cómo estará definida esa estructura con los datos necesarios).

### Clase ExtractorLandmarks

Esta clase estará encargada de obtener los puntos de interés de un rostro a partir de las imágenes provistas por el [Feeder](#clase-feeder). Esta clase abstracta en principio puede tener dos implementaciones:

+ clase ExtractorLandmarksOpenCV, utilizando openCV
+ clase ExtractorLandmarksDlib, utilizando dlib

Estas dos clases utilizarían distintos algoritmos para la deteccion de puntos de interes, basados en distintos papers y con distintos entrenamientos.

![Ejemplo del Feeder](/Diagrama/extractorLandmarks.png)

Diagrama UML de la clase ExtractorLandmarks

### Clase NormalizadorLandmarks

Esta clase deberá normalizar los puntos de interés provistos por el [extractor de landmarks](#clase-extractorlandmarks), es decir, en principio deberá corregir la inclinacion de la cabeza, y deberia "normalizar" los tamaños de los features, pudiendo tomar como referencias los puntos a mitad de cada oreja y el punto central de la pera. Con esto, todas las caras tendrían el mismo tamaño, lo cual podría ser util para una posible comparacion de fotogramas posteriormente (aun asi entiendo que no influiria en el calculo de simetria).
Además, el normalizador podria filtrar solo los landmarks necesarios para el calculo de simetria, reduciendo asi el tamaño de los datos guardados.

### Clase AnalizadorSimetria

Esta clase será la encargada de analizar los puntos de interés normalizados, haciendo algunos calculos geométricos y devolviendo distintas medidas sobre la simetria facial.
En el [paper][1] de referencia, estas medidas se utilizan para luego alimentar un clasificador. Al no tener acceso a los datasets para poder "clasificar" distintos rostros, este ultimo paso se dificulta. Aun asi, debe ser posible obtener un puntaje analizando distintas medidas y comparando ambos lados del rostro.

[1]: https://www.mdpi.com/2076-3417/11/5/2435 "Facial Paralysis Detection on Images Using Key Point Analysis"
