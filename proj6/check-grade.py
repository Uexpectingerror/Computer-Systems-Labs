import sys

if len(sys.argv) < 3:
    print('Usage: python check-grade.py <trace-score> <perf-score>')
    exit(0)

def calculate_score(trace_score, perf_score):
    if perf_score < 56 or trace_score < 0 or trace_score > 11:
        return 0
    else:
        trace_score_w = 0.3 * (trace_score / 11.0) * 100
        if perf_score > 93:
            perf_score_w = 70
        else:
            offset = 95.78672
            divisor = -95.8018483600000
            first_pow = pow((perf_score / 55.86139), 1353.811)
            second_pow = pow((1 + first_pow), 0.006513422)
            perf_score_w = 0.7 * (offset + divisor / second_pow)
        score = round(trace_score_w + perf_score_w)
        return score


trace_score = sys.argv[1]
perf_score = sys.argv[2]

try:
    score = calculate_score(int(sys.argv[1]), int(sys.argv[2]))
    print("Total score: {}".format(score))
except ValueError:
    print('Must pass in integers to trace-score and perf-score')

