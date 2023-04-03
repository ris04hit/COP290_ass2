p1:
	gcc -o part1/obj/main_test part1/src/main.c
	part1/obj/main_test $(arg1) $(arg2) $(arg3) $(arg4) $(arg5)

p2-hashmap_test:
	gcc -o part2/obj/hashmap_test part2/test/hashmap_test.c part2/src/hm.c part2/src/mythread.c part2/src/list.c
	part2/obj/hashmap_test

p2-list_test:
	gcc -o part2/obj/list_test part2/test/list_test.c part2/src/list.c
	part2/obj/list_test

p2-no_yield:
	gcc -o part2/obj/main_no_yield part2/test/main_no_yield.c part2/src/hm.c part2/src/mythread.c part2/src/list.c
	part2/obj/main_no_yield $(arg1) $(arg2) $(arg3) $(arg4) 

p2-race:
	gcc -o part2/obj/main_race     part2/test/main_race.c     part2/src/hm.c part2/src/mythread.c part2/src/list.c
	part2/obj/main_race    $(arg1) $(arg2) $(arg3) $(arg4) 

p2-main:
	gcc -o part2/obj/main          part2/test/main.c          part2/src/hm.c part2/src/mythread.c part2/src/list.c
	part2/obj/main         $(arg1) $(arg2) $(arg3) $(arg4) 

p3:
	gcc -o part3/obj/main          part3/test/main.c          part3/src/hm.c part3/src/mythread.c part3/src/list.c
	part3/obj/main         $(arg1) $(arg2) $(arg3) $(arg4)
