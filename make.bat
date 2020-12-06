if not exist build (
md build
)

call cmake -S %~dp0 -B build