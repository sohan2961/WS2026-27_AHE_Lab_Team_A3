#!/usr/bin/env python3
"""Team A3 software ground truth. Uses only NumPy, no model training."""
from pathlib import Path
import numpy as np

TOKENS, DIM, FF_DIM, EPS = 8, 16, 32, 1e-5
ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "data"
OUT.mkdir(exist_ok=True)


def norm(x, gamma, beta):
    mean = x.mean(axis=-1, keepdims=True)
    variance = ((x - mean) ** 2).mean(axis=-1, keepdims=True)
    return (x - mean) / np.sqrt(variance + np.float32(EPS)) * gamma + beta


def save(name, array):
    # 9 significant figures suffice to round-trip FP32 tensors to text.
    np.savetxt(OUT / name, np.asarray(array, dtype=np.float32).reshape(-1, 1), fmt="%.9g")


def main():
    rng = np.random.default_rng(20261112)
    x = rng.standard_normal((TOKENS, DIM)).astype(np.float32) * np.float32(0.5)
    # Fixed random weights are a functional test, NOT a trained model.
    wq = (rng.standard_normal((DIM, DIM)) * 0.12).astype(np.float32)
    wk = (rng.standard_normal((DIM, DIM)) * 0.12).astype(np.float32)
    wv = (rng.standard_normal((DIM, DIM)) * 0.12).astype(np.float32)
    wo = (rng.standard_normal((DIM, DIM)) * 0.12).astype(np.float32)
    w1 = (rng.standard_normal((DIM, FF_DIM)) * 0.12).astype(np.float32)
    w2 = (rng.standard_normal((FF_DIM, DIM)) * 0.12).astype(np.float32)
    g1 = np.ones(DIM, dtype=np.float32)
    b1 = np.zeros(DIM, dtype=np.float32)
    g2 = np.ones(DIM, dtype=np.float32)
    b2 = np.zeros(DIM, dtype=np.float32)
    weights = np.concatenate([a.ravel() for a in (wq, wk, wv, wo, w1, w2, g1, b1, g2, b2)])
    assert weights.shape == (2112,)
    n1 = norm(x, g1, b1)
    q, k, v = n1 @ wq, n1 @ wk, n1 @ wv
    score = (q @ k.T) * np.float32(0.25)
    shifted = score - score.max(axis=1, keepdims=True)
    softmax = np.exp(shifted)
    softmax /= softmax.sum(axis=1, keepdims=True)
    attn = (softmax @ v) @ wo
    r1 = x + attn
    n2 = norm(r1, g2, b2)
    ff = np.maximum(n2 @ w1, 0.0) @ w2
    result = r1 + ff

    for name, arr in (('input.txt', x), ('weights.txt', weights),
                      ('expected_ln1.txt', n1), ('expected_attention.txt', attn),
                      ('expected_ln2.txt', n2), ('expected_ffn.txt', ff),
                      ('expected_output.txt', result)):
        save(name, arr)
    print(f"Reference generated: {OUT}")
    print(f"Input: {x.shape}, weight floats: {weights.size}, output: {result.shape}")
    print("First output row:", np.array2string(result[0], precision=5))
    print("Reference model: PASS (finite values and expected shapes)")
    assert np.isfinite(result).all()


if __name__ == '__main__':
    main()
