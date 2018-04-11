#!/usr/bin/env bash

DEFAULT_SCALE=33

x=0
y=0
scale=$DEFAULT_SCALE

fractal=m

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
            j) switch_fractal ;;
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
    ./mandelbrot $fractal $w $h $scale $x $y 100 $px $py
    tput cup 0 0
    echo "Position: ($x,$y)"
    echo "Zoom: $scale"
    if [ $fractal = j ]; then
        echo "Parameter: ($px,$py)"
    fi
}

switch_fractal() {
    if [ $fractal = m ]; then
        fractal=j
        px=$x
        py=$y
        m_scale=$scale;
        x=0
        y=0
        scale=$DEFAULT_SCALE
    else
        fractal=m
        x=$px
        y=$py
        scale=$m_scale
    fi
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

