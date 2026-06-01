package main

import "testing"

func TestHello(t *testing.T) {
	got := Hello()
	want := "sadbunny was here"

	if got != want {
		t.Errorf("got %q want %q", got, want)
	}
}