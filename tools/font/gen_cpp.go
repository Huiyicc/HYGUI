package main

import (
	"os"
)

func main() {
	chrs := ""
	outStr := `//
// Created by 19254 on 24-8-26.
//
#include "HYGUI/Text.h"
#include "unordered_map"
#include "tuple"
#include "PrivateDefinition.h"

namespace HYGUI {

const std::unordered_map<char32_t, std::tuple<const char*,const char *>> g_emoji_map = {` + "\n"
	for k, v := range emojis {
		if len(k) > 4 {
			continue
		}
		chrs += k
		outStr += `{U'` + k + `', { "` + v[0] + `","` + v[1] + `"}},` + "\n"
	}
	outStr += "};\n}\n"
	f, err := os.OpenFile("emoji_map.inl", os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0644)
	if err != nil {
		panic(err)
	}
	f.Write([]byte(outStr))
	f.Close()
	f, err = os.OpenFile("emoji_map.txt", os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0644)
	if err != nil {
		panic(err)
	}
	f.Write([]byte(chrs))
	f.Close()

}
