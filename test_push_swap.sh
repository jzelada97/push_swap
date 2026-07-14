#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

PASS=0
FAIL=0

test_error() {
    local desc="$1"
    shift
    local result=$(./push_swap "$@" 2>&1)
    if [ "$result" = "Error" ]; then
        echo -e "${GREEN}✓${NC} $desc"
        ((PASS++))
    else
        echo -e "${RED}✗${NC} $desc (esperado: Error, obtenido: '$result')"
        ((FAIL++))
    fi
}

test_ok() {
    local desc="$1"
    local args="$2"
    local result=$(./push_swap $args 2>&1)
    if [ -z "$result" ]; then
        echo -e "${GREEN}✓${NC} $desc"
        ((PASS++))
    else
        echo -e "${RED}✗${NC} $desc (esperado: sin output, obtenido: '$result')"
        ((FAIL++))
    fi
}

test_checker_ok() {
    local desc="$1"
    local args="$2"
    local result=$(./push_swap $args | ./checker $args 2>&1)
    if [ "$result" = "OK" ]; then
        echo -e "${GREEN}✓${NC} $desc"
        ((PASS++))
    else
        echo -e "${RED}✗${NC} $desc (esperado: OK, obtenido: '$result')"
        ((FAIL++))
    fi
}

test_ops_count() {
    local desc="$1"
    local args="$2"
    local max_ops="$3"
    local flag="${4:---adaptive}"
    local count=$(./push_swap $flag $args | wc -l)
    if [ "$count" -le "$max_ops" ]; then
        echo -e "${GREEN}✓${NC} $desc ($count ops)"
        ((PASS++))
    else
        echo -e "${RED}✗${NC} $desc ($count ops > $max_ops)"
        ((FAIL++))
    fi
}

echo "=========================================="
echo "    PUSH_SWAP - TEST EXHAUSTIVO"
echo "=========================================="

echo ""
echo "=== 1. MANEJO DE ERRORES ==="

test_error "No entero: abc" abc
test_error "No entero mezclado: 1 abc 3" 1 abc 3
test_error "Decimal: 1.5" 1.5
test_error "Fuera de rango: INT_MAX+1" 2147483648
test_error "Fuera de rango: INT_MIN-1" -2147483649
test_error "Duplicados: 1 2 3 2" 1 2 3 2
test_error "Duplicados: 5 5 5" 5 5 5
test_error "String con solo espacios" "   "
test_error "String con muchos espacios" "      "
test_error "Flag inválido" --invalid 1 2 3
test_error "Múltiples flags de estrategia" --simple --medium 1 2 3
test_error "Signos múltiples: ++" ++5
test_error "Signos múltiples: --" --3
test_error "Signo solo: +" +
test_error "Signo solo: -" -

echo ""
echo "=== 2. CASOS LÍMITE VÁLIDOS ==="

test_ok "Sin argumentos" ""
test_ok "1 elemento" 42
test_ok "Ya ordenado: 1 2 3 4 5" "1 2 3 4 5"
test_ok "Ya ordenado: -3 -2 -1 0 1" "-3 -2 -1 0 1"

echo ""
echo "=== 3. ORDENACIÓN CORRECTA (checker) ==="

test_checker_ok "2 elementos desordenados" "2 1"
test_checker_ok "3 elementos" "3 2 1"
test_checker_ok "5 elementos" "5 3 1 4 2"
test_checker_ok "10 elementos" "9 2 7 1 8 3 6 4 5 0"
test_checker_ok "Negativos" "-5 -3 -1 -4 -2"
test_checker_ok "Mixtos" "-2 5 0 -7 3 1 -4"

echo ""
echo "=== 4. LÍMITES INT ==="

test_checker_ok "INT_MIN, 0, INT_MAX" "-2147483648 0 2147483647"
test_checker_ok "Solo INT_MIN e INT_MAX" "-2147483648 2147483647"

echo ""
echo "=== 5. RENDIMIENTO (100 números) ==="

ARG100=$(python3 -c 'import random; print(" ".join(map(str, random.sample(range(1000), 100))))')
test_ops_count "100 nums --adaptive < 2000 (minimo)" "$ARG100" 2000 "--adaptive"
test_ops_count "100 nums --medium < 700 (excelente)" "$ARG100" 700 "--medium"
test_checker_ok "100 nums verificación con checker" "$ARG100"

echo ""
echo "=== 6. RENDIMIENTO (500 números) ==="

ARG500=$(python3 -c 'import random; print(" ".join(map(str, random.sample(range(10000), 500))))')
test_ops_count "500 nums --adaptive < 12000 (minimo)" "$ARG500" 12000 "--adaptive"
test_ops_count "500 nums --medium < 5500 (excelente)" "$ARG500" 5500 "--medium"
test_checker_ok "500 nums verificación con checker" "$ARG500"

echo ""
echo "=== 7. CHECKER - OPERACIONES INVÁLIDAS ==="

CHECK_INVALID=$(echo "xyz" | ./checker "1 2 3" 2>&1)
if [ "$CHECK_INVALID" = "Error" ]; then
    echo -e "${GREEN}✓${NC} Checker detecta operación inválida"
    ((PASS++))
else
    echo -e "${RED}✗${NC} Checker no detecta operación inválida"
    ((FAIL++))
fi

CHECK_OK=$(echo "" | ./checker "1 2 3" 2>&1)
if [ "$CHECK_OK" = "OK" ]; then
    echo -e "${GREEN}✓${NC} Checker OK en lista ordenada sin operaciones"
    ((PASS++))
else
    echo -e "${RED}✗${NC} Checker falla en lista ordenada"
    ((FAIL++))
fi

CHECK_KO=$(echo "sa" | ./checker "1 2 3" 2>&1)
if [ "$CHECK_KO" = "KO" ]; then
    echo -e "${GREEN}✓${NC} Checker KO cuando queda desordenado"
    ((PASS++))
else
    echo -e "${RED}✗${NC} Checker no detecta desorden"
    ((FAIL++))
fi

echo ""
echo "=========================================="
echo "    RESUMEN"
echo "=========================================="
echo -e "${GREEN}Pasados: $PASS${NC}"
echo -e "${RED}Fallados: $FAIL${NC}"
echo "=========================================="

if [ $FAIL -eq 0 ]; then
    echo -e "${GREEN}¡Todos los tests pasaron!${NC}"
    exit 0
else
    echo -e "${RED}Algunos tests fallaron.${NC}"
    exit 1
fi
