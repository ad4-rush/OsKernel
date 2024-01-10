all: Q2_part1.c Q2_part3.c Q2_part2.c counter_function.c 
	gcc -o counter_function counter_function.c
	gcc -o Q2_part1 Q2_part1.c
	gcc -o Q2_part2 Q2_part2.c
	gcc -o Q2_part3 Q2_part3.c
	> output.txt
	sudo taskset --cpu-list 1 "./Q2_part1"
	sudo taskset --cpu-list 1 "./Q2_part2"
	sudo taskset --cpu-list 1 "./Q2_part3"
	python plotting.py
clean:
	rm counter_function
	rm Q2_part1
	rm Q2_part2
	rm Q2_part3
	rm output.txt