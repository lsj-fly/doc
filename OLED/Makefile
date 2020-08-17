a=1
obj=main.o oled.o
exe:$(obj)
	gcc -o exe $(obj)
main.o:main.c
	gcc -c main.c
oled.o:oled.c
	gcc -c oled.c
ifeq ($(a),1)
	@echo "succeed!"
else
	@echo "error!"
endif
.PHONY:clean
clean:
	rm -rf *o exe

