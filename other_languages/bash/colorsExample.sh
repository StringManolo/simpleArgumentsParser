#!/bin/bash

source ./parseCLI
parse_cli "$@"

if cli noArgs; then
    echo $(cli color blue "Arguments needed")
fi

if cli noArgs; then
    echo $(cli color bold red "ERROR: Arguments needed")
fi

if cli noArgs; then
    echo $(cli color bold white bg_red "CRITICAL ERROR")
fi

if cli s h || cli c help; then
    cli color bold cyan "Help Menu:"
    echo ""
    cli color green "This is just an example"
    exit 0
fi

error_msg=$(cli color red "Something went wrong")
success_msg=$(cli color green "Operation successful")
warning_msg=$(cli color yellow "Warning: proceeding anyway")

info() {
    cli color cyan "[INFO] $1"
}

success() {
    cli color green "[SUCCESS] $1"
}

error() {
    cli color bold red "[ERROR] $1"
}

warning() {
    cli color yellow "[WARNING] $1"
}

info "Starting process..."
success "Operation completed"
error "Failed to connect"
warning "Resource running low"

verbose=false

if cli noArgs; then
    echo $(cli color bold blue "Arguments needed")
    exit 1
fi

if cli s h || cli c help; then
    cli color bold magenta "Help Menu:"
    echo ""
    cli color cyan "Uso: $0 [comando] [opciones]"
    cli color green "Comandos disponibles: add, send, show, contacts, delete"
    exit 0
fi

if cli s v || cli c verbose; then
    verbose=true
    cli color dim yellow "[VERBOSE] Modo detallado activado"
fi
