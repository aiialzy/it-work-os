package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"os"
	"os/exec"
	"strings"
)

var base_address = 0x80400000

const step = 0x20000

var requiredFiles = []string{"start.o", "string.o", "printf.o", "syscall.o", "start_globl.o"}
var files = []string{"power3.o", "power5.o", "power7.o", "sleep.o"}

func main() {
	buf, err := os.ReadFile("user/user.ld.template")
	if err != nil {
		log.Fatalln(err)
	}
	for i, f := range requiredFiles {
		requiredFiles[i] = "user/" + f
	}
	str := string(buf)
	lines := strings.Split(str, "\n")
	for i := 0; i < 4; i++ {
		addr_line := fmt.Sprintf("BASE_ADDRESS = 0x%x;", base_address)
		pre := lines[:3]
		after := lines[4:]
		genLines := append([]string{}, pre...)
		genLines = append(genLines, addr_line)
		genLines = append(genLines, after...)
		ldScript := strings.Join(genLines, "\n")
		if err = os.WriteFile("user/user.ld", []byte(ldScript), 0766); err != nil {
			log.Fatalln(err)
		}

		command := "riscv64-unknown-elf-ld"
		args := []string{"-T", "user/user.ld", "-o"}
		arg1 := fmt.Sprintf("build/%v", files[i][:len(files[i])-2])
		args = append(args, arg1)
		args = append(args, requiredFiles...)
		args = append(args, fmt.Sprintf("user/%v", files[i]))
		cmd := exec.Command(command, args...)
		out, _ := cmd.StdoutPipe()
		errout, _ := cmd.StderrPipe()

		go handlerErr(errout)

		if err := cmd.Start(); err != nil {
			log.Fatalf("没跑起来: %v\n", err)
		}
		in := bufio.NewScanner(out)
		for in.Scan() {
			fmt.Println(in.Text())
		}
		cmd.Wait()

		base_address += step
	}
}

//开启一个协程来输出错误
func handlerErr(errReader io.ReadCloser) {
	in := bufio.NewScanner(errReader)
	for in.Scan() {
		fmt.Println(in.Text())
	}
}
