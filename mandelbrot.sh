#!/usr/bin/env bash

x=0
y=0
scale=33

main() {
    init
    while :; do
        read -rsn1 -d ''
        case "${REPLY}" in
            w) y=$(echo "$y $scale" | awk '{printf "%f", $1+3/$2}') ;;
            s) y=$(echo "$y $scale" | awk '{printf "%f", $1-3/$2}') ;;
            d) x=$(echo "$x $scale" | awk '{printf "%f", $1+6/$2}') ;;
            a) x=$(echo "$x $scale" | awk '{printf "%f", $1-6/$2}') ;;
            q) scale=$(echo "$scale" | awk '{printf "%f", $1/1.1}') ;;
            e) scale=$(echo "$scale" | awk '{printf "%f", $1*1.1}') ;;
            ?) cleanup ;;
        esac
        draw
    done
}

init() {
    tput smcup
    tput civis
    tput clear

    trap cleanup INT

    resize
    trap resize SIGWINCH
}

draw() {
    tput cup 0 0
    ./mandelbrot $w $h $scale $x $y 100
    tput cup 0 0
    echo $x
    echo $y
    echo $scale
}

resize() {
    w=$(tput cols)
    h=$(tput lines)
    draw
}

cleanup() {
    tput rmcup
    tput cnorm
    exit 0
}

main
