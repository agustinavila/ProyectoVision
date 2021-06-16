# Proyecto Vision

Proyecto final para las materias "Vision Artificial" y "Complementos de Informatica"
El proyecto consiste en un programa capaz de obtener imagenes de distintos medios, detectar caras y analizar su simetria. Ademas, deberia ser capaz de generar reportes y mostrar fotogramas claves, donde la asimetria sea maxima o donde se detecte claramente cierta expresion facial (sonrisa, ceño fruncido, levantar cejas, etc). La idea de la implementación está basada en [este paper][1].

## Desarrollo

El software consistira de varias clases, "concatenadas" entre si utilizando un esquema de observadores.

![Esquema del funcionamiento general](/Diagrama/proyectoVision.png).

En el esquema anterior, las flechas indican "observadores de"

### Clase Feeder { : #feeder}

 Habrá una clase (por ahora llamada feeder, no se si es un nombre claro) encargada de obtener los fotogramas a analizar. De ésta se derivan tres clases (por ahora) que heredan algunos metodos base pero implementados con distintos fines. Las tres clases que heredan de Feeder, serán:

+ VideoFeeder, pensada para trabajar con videos
+ WebcamFeeder, pensada para adquirir fotogramas de una webcam
+ KinectFeeder, pensada para adquirir fotogramas de una kinect utilizando libfreenect2.

Estas clases tendrán métodos para actualizar sus observadores ([FrameLogger](#framelogger) y [ExtractorLandmarks](#extractorlandmarks)).
Además, tendrán un método para obtener fotogramas en un momento determinado[^2]?

![Ejemplo del Feeder](/Diagrama/feeder.png)

Ejemplo en UML de la clase "feeder"

### Clase FrameLogger {: #framelogger }

Esta clase estará encargada de registrar los frames provistos por el [Feeder](#feeder), ya que será un observador. Debe tener un metodo de actualizacion que consista en guardar el archivo de imagen en algun lugar en particular, con un nombre que lo identifique unicamente, y que de alguna manera quede linkeado a una "base de datos" [^1] .

### Clase ExtractorLandmarks {: #extractorlandmarks }

Esta clase estará encargada de obtener los puntos de interés de un rostro a partir de las imágenes provistas por el [Feeder](#feeder). Esta clase abstracta en principio puede tener dos implementaciones:

+ clase ExtractorLandmarksOpenCV, utilizando openCV
+ clase ExtractorLandmarksDlib, utilizando dlib

Estas dos clases utilizarían distintos algoritmos para la deteccion de puntos de interes, basados en distintos papers y con distintos entrenamientos.

![Ejemplo del Feeder](/Diagrama/extractorLandmarks.png)

Diagrama UML de la clase ExtractorLandmarks


### Clase NormalizadorLandmarks { : #normalizadorlandmarks}

Esta clase deberá normalizar los puntos de interés provistos por el [extractor de landmarks](#extractorlandmarks), es decir, en principio deberá corregir la inclinacion de la cabeza, y deberia "normalizar" los tamaños de los features, pudiendo tomar como referencias los puntos a mitad de cada oreja y el punto central de la pera. Con esto, todas las caras tendrían el mismo tamaño, lo cual podría ser util para una posible comparacion de fotogramas posteriormente (aun asi entiendo que no influiria en el calculo de simetria).
Además, el normalizador podria filtrar solo los landmarks necesarios para el calculo de simetria, reduciendo asi el tamaño de los datos guardados.

### Clase AnalizadorSimetria { : #analizadorsimetria}

Esta clase será la encargada de analizar los puntos de interés normalizados, haciendo algunos calculos geométricos y devolviendo distintas medidas sobre la simetria facial.
En el [paper][1] de referencia, estas medidas se utilizan para luego alimentar un clasificador. Al no tener acceso a los datasets para poder "clasificar" distintos rostros, este ultimo paso se dificulta. Aun asi, debe ser posible obtener un puntaje analizando distintas medidas y comparando ambos lados del rostro.

[^1]: Me falta definir cómo estará definida esa estructura con los datos necesarios.
[^2]: Es decir, usar algun tipo de semaforo para esperar a cuando el extractor se libere, y recien ahi proveerle otro fotograma? Entiendo que el cuello de botella será el extractor de landmarks.

[1]: https://www.mdpi.com/2076-3417/11/5/2435 "Facial Paralysis Detection on Images Using Key Point Analysis"
