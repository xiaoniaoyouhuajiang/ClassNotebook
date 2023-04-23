package main

import (
	"fmt"
	"time"
)

func main1() {
	done := make(chan int, 1)

	go func() {
		time.Sleep(5 * time.Second)
		done <- 1
	}()

	fmt.Println("waiting")
	<-done
	fmt.Println("done")
}
