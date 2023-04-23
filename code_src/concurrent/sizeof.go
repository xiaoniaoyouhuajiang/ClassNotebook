package main

import (
	"fmt"
	"unsafe"
)

type Man struct {
	Name string
	Age  int
}

func main() {
	m := Man{Name: "John", Age: 20}
	var t []string

	fmt.Println("man size:", unsafe.Sizeof(m))
	fmt.Println("name size:", unsafe.Sizeof(m.Name))
	fmt.Println("age size:", unsafe.Sizeof(m.Age))
	fmt.Println("empty list size:", unsafe.Sizeof(t))
}
