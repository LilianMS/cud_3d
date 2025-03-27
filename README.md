# cud_3d

    - para rodar com valgrind e supressions:
        - valgrind --suppressions=mlx42.supp  ./cub3D assets/map/simple_map.cub
        - valgrind --leak-check=full --show-leak-kinds=all --suppressions=mlx42.supp ./cub3D assets/map/simple_map.cub