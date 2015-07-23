APPNAME=GOCOMMON
APPPATH=uaq@115.231.98.84:/home/uaq/opbin/zhangpengpeng/mygo/src/$(APPNAME)

$(APPNAME): main.go
	go build -o $(APPNAME) main.go

clean:
	-rm $(APPNAME)
	-rm logs/*
	@echo 
	@echo Clean Success

run:
	./$(APPNAME) > logs/$(APPNAME)_stdout.log 2>&1 &

kill:
	killall $(APPNAME)

ps:
	ps -ef | grep $(APPNAME)
	netstat -nlp | grep $(APPNAME)

toS:
	rsync -a * $(APPPATH)

getS:
	rsync -a $(APPPATH)/* .

