import optuna
import subprocess


def calc_score(P1, P2, P3, P4):
    cp = subprocess.run(
        ["./src/cpp/param",
         str(P1),
         str(P2),
         str(P3),
         str(P4)],
        capture_output=True)
    print(cp.stderr.decode('utf-8'))
    return int(cp.stdout.split()[-1])


def objective(trial):
    print("start")
    P1 = trial.suggest_int("BOUNDARY_LOOPCNT", 5, 20)
    P2 = trial.suggest_int("SECURE_PATTERN_NUM", 5, 30)
    P3 = trial.suggest_int("BW_1", 100, 300)
    P4 = trial.suggest_int("BW_2", 100, 1000)
    print("params:", P1, P2, P3, P4, sep=" ")
    score = calc_score(P1, P2, P3, P4)
    print(score)
    print("done")
    return score


if __name__ == "__main__":
    print("setup start")
    study = optuna.create_study(
        direction="maximize",
        storage="sqlite:///ahc014_100.db",
        study_name="tune_range",
        load_if_exists=True,
    )
    print("setup done")
    study.optimize(objective)
