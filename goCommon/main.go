package main

import (
	"runtime"
	"goCommon/g"
	_ "goCommon/routers"
	"github.com/astaxie/beego"
)

func main() {
	cpuNum := runtime.NumCPU()
	if cpuNum > 1 {
		runtime.GOMAXPROCS(cpuNum - 1)
	}

	g.ProgramName = "goCommon"
	g.InitGlobal()
	g.Log.Info(g.ProgramName + " Start...")

	beego.Run()
}

