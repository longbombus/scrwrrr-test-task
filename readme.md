# Запуск
Склонируйте репозиторий и откройте проект в своей IDE, например:

    ```
    git clone git@github.com:longbombus/scrwrrr-test-task.git
    cd scrwrrr-test-task
    mkdir build
    cd build
    cmake .. -GXCode
    ```

# Шейдеры
[Вершинный шейдер `emissive.vert`](https://github.com/longbombus/scrwrrr-test-task/blob/master/Resources/shaders/emissive.vert)

[Фрагментный шейдер `emissive.frag`](https://github.com/longbombus/scrwrrr-test-task/blob/master/Resources/shaders/emissive.frag)

Параметры шейдера:
- `u_texture` -- альбедо-текстура
- `u_emissive` -- текстура эмиссии
- `u_dayNightFactor` -- 0 день, 1 ночь
- `u_nightColor` -- оттенок albedo-текстуры в ночное время

Вершинный шейдер -- тривиальный.

Фрагментный шейдер делает семплинг двух текстур и смешивает их так, что в дневное время первая отображается как Unlit, а в ночное время вторая аддитивно накладывается на первую затененную ночным цветом.

Для улучшения производительности можно:
- реализовать инстансинг для отрисовки большого количества одинаковых объектов;
- перенести `u_emissive` в альфа-канал альбедо-текстуры убрав второй семплинг, добавляя конкретный цвет по маске;
- если `u_emissive` обязательно должен быть разноцветным, то от второго семплинга можно избавиться либо выполняя его при `u_dayNightFactor > EPS` (но бранчинг может свести на нет выигрыш, нужно делать замеры на конкретных девайсах, чтобы принять решение), либо сделать shader-variant который будет использоваться при `u_dayNightFactor < EPS` и не использовать второй семплинг;
- избавиться от `u_dayNightFactor` (был указан в ТЗ) и слить его с `u_nightColor` в один итоговый `u_lightColor`, который будет вычисляться на CPU. Значение `u_dayNightFactor` для подмешивания `u_emissive` можно будет взять из `u_lightColor.a`;
