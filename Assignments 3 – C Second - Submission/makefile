PokemonsBattles: LinkedList.o MainSecond.o MaxHeap.o Pokemon.o BattleByCategory.o
	gcc LinkedList.o MainSecond.o MaxHeap.o Pokemon.o BattleByCategory.o -o PokemonsBattles
LinkedList.o: LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c
MainSecond.o: MainSecond.c Pokemon.h Defs.h BattleByCategory.h
	gcc -c MainSecond.c
MaxHeap.o: MaxHeap.c MaxHeap.h Defs.h
	gcc -c MaxHeap.c
Pokemon.o: Pokemon.c Pokemon.h Defs.h 
	gcc -c Pokemon.c	
BattleByCategory.o: BattleByCategory.c BattleByCategory.h LinkedList.h Defs.h MaxHeap.h
	gcc -c BattleByCategory.c
clean:
	rm -f *.o
 	
