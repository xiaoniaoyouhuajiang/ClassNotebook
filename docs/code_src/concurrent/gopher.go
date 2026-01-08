package concurrent

import (
	"fmt"	"time"
)


type Gopher struct {
	Name       string
	Id         int
	CoffeeName string
}

var coffeeMachine = CoffeeMachine()

// 制造咖啡
func (this *Gopher) MakeCoffee(coffeeName string) {
	if coffeeMachine.CoffeeName == "" {
		coffeeMachine.CoffeeName = coffeeName
		coffeeMachine.Gopher = *this
		fmt.Println("Gopher", this.Id, "Make Coffee",coffeeMachine.coffeeName)
		time.Sleep(10 * time.Second)
	}
}
