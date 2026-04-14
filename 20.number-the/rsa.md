# RSA Public-Key Cryptosystem 

## Public-Key Cryptosystems — The Idea

Each participant has two keys:
- **Public key** $P$ — published openly, used to *encrypt* messages sent *to* you
- **Secret key** $S$ — kept private, used to *decrypt* messages sent to you

The keys are a matched pair — inverse functions of each other:

$$M = S(P(M)) = P(S(M)) \quad \forall M \in \mathcal{D}$$

Security requirement: knowing $P$ must make it **computationally infeasible** to compute $S$.

---

## Encryption & Digital Signatures

**Encryption** (Bob → Alice):
1. Bob obtains Alice's public key $P_A$
2. Bob computes ciphertext $C = P_A(M)$ and sends $C$
3. Alice recovers $M = S_A(C)$ — only she can, since only she knows $S_A$

**Digital Signature** (Alice → Bob):
1. Alice computes signature $\sigma = S_A(M')$ using her secret key
2. Alice sends the pair $(M', \sigma)$
3. Bob verifies by checking $M' = P_A(\sigma)$ — if it holds, the message is authentic

> A signed message is **not** encrypted. To get both: sign first, then encrypt the signed pair.

---

## RSA Key Generation

1. Choose two large random primes $p \neq q$ (e.g. 512 bits each)
2. Compute $n = pq$
3. Choose small odd $e$ with $\gcd(e,\ \phi(n)) = 1$, where $\phi(n) = (p-1)(q-1)$
4. Compute $d \equiv e^{-1} \pmod{\phi(n)}$ (multiplicative inverse of $e$)
5. **Public key:** $P = (e, n)$
6. **Secret key:** $S = (d, n)$

---

## RSA Transformations

**Encrypt / apply public key:**
$$P(M) = M^e \bmod n \tag{31.35}$$

**Decrypt / apply secret key:**
$$S(C) = C^d \bmod n \tag{31.36}$$

Both use **modular exponentiation** (repeated squaring) — $O(\beta^3)$ bit operations.

| Operation | Key used | Cost |
|---|---|---|
| Encrypt / verify signature | Public key $(e, n)$, $\lg e = O(1)$ | $O(\beta^2)$ bit ops |
| Decrypt / sign | Secret key $(d, n)$, $\lg d \leq \beta$ | $O(\beta^3)$ bit ops |

---

## Correctness of RSA (Theorem 31.36)

**Claim:** $P(S(M)) = S(P(M)) = M^{ed} \equiv M \pmod{n}$

**Proof sketch:**

Since $e$ and $d$ are multiplicative inverses mod $\phi(n) = (p-1)(q-1)$:

$$ed = 1 + k(p-1)(q-1) \quad \text{for some integer } k$$

For $M \not\equiv 0 \pmod{p}$, by Fermat's little theorem:

$$M^{ed} = M \cdot (M^{p-1})^{k(q-1)} \equiv M \cdot 1^{k(q-1)} \equiv M \pmod{p}$$

The same holds mod $q$. By **CRT (Corollary 31.29)**:

$$M^{ed} \equiv M \pmod{n} \quad \blacksquare$$

---

## Security

RSA security rests on the **hardness of integer factorization**:
- If an adversary can factor $n = pq$, they recover $\phi(n) = (p-1)(q-1)$ and compute $d$ from $e$ — breaking RSA completely.
- The converse (breaking RSA ⟹ factoring) is unproven, but no easier attack has been found in decades of research.
- In practice, $n$ should be 768–2048+ bits to resist factoring attacks.

---

## Practical Optimizations

**Hybrid encryption** — RSA is slow for long messages:
1. Alice picks a random symmetric key $K$
2. Encrypts $M$ with fast symmetric cipher → ciphertext $C$
3. Encrypts $K$ with Bob's RSA public key → $P_B(K)$
4. Sends $(C,\ P_B(K))$ to Bob

**One-way hash for signatures** — avoids signing the whole message:
1. Compute short fingerprint $h(M)$ (e.g. 160-bit SHA)
2. Sign only the fingerprint: $\sigma = S_A(h(M))$
3. Verification: check $P_A(\sigma) = h(M)$

**Certificates** — a trusted authority $T$ signs Alice's public key $P_A$, so recipients can verify they have the real key without contacting Alice directly.
