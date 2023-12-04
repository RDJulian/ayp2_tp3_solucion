# ayp2_tp3_solucion

Posible solución (acotada) del TP3 grupal de AyP2.

// La solución es acotada en el sentido de que no se codea la interacción con el usuario.
// El simulador "se juega solo". La dificultad del TP no pasa por recibir y validar inputs del usuario,
// por lo que se omite en la posible solución. Lo implementado es, en mi opinión, bastante representativo
// de por donde iba la mano. Posiblemente, la parte mas dificil de entender es la clase "ConversorTablero".
// El codigo empezo siendo bastante modular, hasta que implementé el grafo del caso borde y se desmoronó.
// La idea general, es que se parte de una posible representación matricial del problema y me aprovecho de eso
// para generar todos los grafos, asociando cada indice bidimensional i, j con uno unidimensional de la forma
// i * col + j. En un 3x3, el (0,0) es 0, (0,1) es 1, (2,2) es 8, etc...
// De ahi, es facil de entender (creo), que el (0,0) conecta con el (0,1) y (1,0) pero no con el (0,-1) ni (-1,0)...
// Finalmente, teniendo las dimensiones del tablero (matriz), es facil volver de indice unidimensional al bidimensional.
// El unico método que falta implementar y que merece un comentario es el de "mover a James en un casillero".
// Lo unico que puede ocurrir, en ese caso, potencialmente, es que al mover a James, se ahuyenta a un Pyramid Head.
// La forma en que pensé resolverlo es eliminar ese Pyramid Head al mover a James, luego volver a calcular los grafos.
// Se equipan armas debiles siempre que sea posible porque se calcula el mejor camino posible, ya sea con un arma
// equipada o no.