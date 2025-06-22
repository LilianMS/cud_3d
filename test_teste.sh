#!/bin/bash

# Arquivo de saída para registrar os resultados
output_file="test_results.log"
> "$output_file"

# Caminho para o programa cub3D
program="./cub3D"

# Diretório contendo os arquivos de teste
test_dir="maps"

# Verifica se o diretório de testes existe
if [ ! -d "$test_dir" ]; then
    echo "Erro: Diretório '$test_dir' não encontrado." | tee -a "$output_file"
    exit 1
fi

# Itera sobre todos os arquivos no diretório de testes
for test_file in "$test_dir"/*.cub; do
    if [ -f "$test_file" ]; then
        echo "Executando teste com o arquivo: $test_file" | tee -a "$output_file"
        
        # Executa o programa com o arquivo de teste
        $program "$test_file" > /dev/null 2>&1
        if [ $? -eq 0 ]; then
            echo "Teste com '$test_file': SUCESSO" | tee -a "$output_file"
        else
            echo "Teste com '$test_file': ERRO" | tee -a "$output_file"
        fi
    else
        echo "Nenhum arquivo .cub encontrado no diretório '$test_dir'." | tee -a "$output_file"
    fi
done

echo "Testes concluídos. Resultados salvos em '$output_file'."