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
    + [Clase ExtractorLandmarksOpenCV](#clase-extractorlandmarksopencv)
    + [Clase ExtractorLandmarksDlib](#clase-extractorlandmarksdlib)
  + [Clase analizadorLandmarks](#clase-normalizadorlandmarks)

## Desarrollo

El software consiste en varias clases concatenadas entre si.

![Esquema del funcionamiento general](/Diagrama/proyectoVision.png).

El sistema instancia los objetos necesarios a partir de argumentos pasados al mismo(Falta), con las clases concretas necesarias segun el caso. Si no se pasan argumentos, intenta abrir una webcam y utilizar un archivo de entrenamiento por defecto.

## Argumentos

*no esta realizado aun.*

## Clases

A continuacion, se detallan las distintas clases base que compondran al sistema.

### Clase Feeder

 Clase encargada de obtener los fotogramas a analizar. De ésta se derivan tres clases para proveer frames de distintos medios. Las tres clases que heredan de Feeder, serán:

+ VideoFeeder, pensada para trabajar con videos.
+ WebcamFeeder, pensada para adquirir fotogramas de una webcam.
+ KinectFeeder, pensada para adquirir fotogramas de una kinect utilizando libfreenect2.

Estas clases tendrán un método general para devolver un fotograma del tipo `cv::Mat` que serán utilizados por los objetos de las clases ([FrameLogger](#clase-framelogger) y [ExtractorLandmarks](#clase-extractorlandmarks)).

![Ejemplo del Feeder](/Diagrama/feeder.png)

Ejemplo en UML de la clase "feeder"

### Clase FrameLogger

Esta clase está encargada de registrar los frames provistos por el [Feeder](#clase-feeder). Por el momento, va registrando los fotogramas en un video por defecto. Debe tener un metodo de actualizacion que consista en guardar el archivo de imagen en algun lugar en particular, con un nombre que lo identifique unicamente, y que de alguna manera quede linkeado a una "base de datos".

### Clase ExtractorLandmarks

Esta clase está encargada de obtener los puntos de interés de un rostro a partir de las imágenes provistas por el [Feeder](#clase-feeder). Esta clase abstracta en principio tiene dos implementaciones:

+ clase ExtractorLandmarksOpenCV, utilizando openCV
+ clase ExtractorLandmarksDlib, utilizando dlib

Estas dos clases utilizarían distintos algoritmos para la deteccion de puntos de interes, basados en distintos papers y con distintos entrenamientos.

#### Clase ExtractorLandmarksOpenCV

Esta clase está basada en las librerias de openCV.

#### Clase ExtractorLandmarksDlib

Esta clase está basada en las librerias de dlib

![Ejemplo del Feeder](/Diagrama/extractorLandmarks.png)

Diagrama UML de la clase ExtractorLandmarks

### Clase AnalizadorLandmarks

Esta clase normaliza los puntos de interés provistos por el [extractor de landmarks](#clase-extractorlandmarks), es decir, corrige la inclinacion de la cabeza, tomando como referencias los puntos a mitad de cada oreja. Con esto, calcula la simetria de la cara basándose en algunos puntos particulares(Elegidos medio aleatoriamente)
Respecto a la simetria, la clase será la encargada de analizar los puntos de interés normalizados, haciendo algunos calculos geométricos y devolviendo distintas medidas sobre la simetria facial.
En el [paper][1] de referencia, estas medidas se utilizan para luego alimentar un clasificador. Al no tener acceso a los datasets para poder "clasificar" distintos rostros, este ultimo paso se dificulta. Aun asi, debe ser posible obtener un puntaje analizando distintas medidas y comparando ambos lados del rostro.
Además, el normalizador podria filtrar solo los landmarks necesarios para el calculo de simetria, reduciendo asi el tamaño de los datos guardados.
También debería devolver un vector con cada parte de la cara detectada (es decir, segmentar cejas, ojos, boca, nariz...).

## Por Hacer

+ [ ] Logger de informacion relevante
+ [ ] Pasarle argumentos
+ [ ] Terminar VideoFeeder
+ [ ] Terminar KinectFeeder

[1]: https://www.mdpi.com/2076-3417/11/5/2435 "Facial Paralysis Detection on Images Using Key Point Analysis"
