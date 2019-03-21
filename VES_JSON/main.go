package main
import (
	"fmt"
	"os"
	"encoding/json"
)

type Profil struct {
	Curves []Curve
}

type Coords struct {
	x string
	y string
	z string
}

type Curve struct {
	Name string
	Coordinates []Coords
	Samples Sample
}

type Sample struct {
	AB2 []float32
	RoKF []float32
	RokT []float32
}

func main()  {
	file, _ := os.Open("D:\\GIT-REPOS\\ves\\VES_JSON\\ves.json")
	decoder := json.NewDecoder(file)
	profil := new(Profil)
	err := decoder.Decode(&profil)
	if err != nil {
		// handle it
		fmt.Println("Ошибка!")
	} else {
		fmt.Println("%v", profil)
	}

}