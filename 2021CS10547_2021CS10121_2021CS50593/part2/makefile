st := `find ./data -mindepth 1`

list:
	gcc -o obj/list_test test/list_test.c src/list.c
	./obj/list_test

hash:
	gcc -o obj/hashmap_test test/hashmap_test.c src/list.c src/hm.c
	./obj/hashmap_test

main:
	gcc -o obj/main test/main.c src/hm.c src/list.c src/mythread.c
	obj/main $(st)