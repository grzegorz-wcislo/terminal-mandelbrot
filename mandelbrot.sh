#!/usr/bin/env bash

x=0
y=0
scale=33

jx=0
jy=0
jscale=33

fractal=m

main() {
    init
    while :; do
        read -rsn1 -d ''
        if [ $fractal = m ]; then
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
        else
            case "${REPLY}" in
                w) jy=$(echo "$jy $jscale" | awk '{printf "%f", $1+3/$2}') ;;
                s) jy=$(echo "$jy $jscale" | awk '{printf "%f", $1-3/$2}') ;;
                d) jx=$(echo "$jx $jscale" | awk '{printf "%f", $1+6/$2}') ;;
                a) jx=$(echo "$jx $jscale" | awk '{printf "%f", $1-6/$2}') ;;
                q) jscale=$(echo "$jscale" | awk '{printf "%f", $1/1.1}') ;;
                e) jscale=$(echo "$jscale" | awk '{printf "%f", $1*1.1}') ;;
                j) switch_fractal ;;
                ?) cleanup ;;
            esac
        fi
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
    if [ $fractal = m ]; then
        ./mandelbrot m $w $h $scale $x $y 100
        tput cup 0 0
        echo "Position: ($x,$y)"
        echo "Zoom: $scale"
    else
        ./mandelbrot j $w $h $jscale $jx $jy 100 $x $y
        tput cup 0 0
        echo "Position: ($jx,$jy)"
        echo "Zoom: $jscale"
        echo "Parameter: ($x,i$y)"
    fi
}

switch_fractal() {
    if [ $fractal = m ]; then
        fractal=j
        jx=0
        jy=0
        jscale=33
    else
        fractal=m
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

