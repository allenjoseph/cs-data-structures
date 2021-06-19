function matrixChainOrder(p) {
    const n = p.length - 1;
    const m = {};
    const s = {};

    for (let i = 1; i <= n; i++) {
        m[`${i},${i}`] = 0;
        console.log(`m[${i},${i}]=${m[`${i},${i}`]}`);
    }

    for (let l = 2; l <= n; l++) {

        for (let i = 1; i <= n - l + 1; i++) {
            const j = i + l - 1;
            m[`${i},${j}`] = Infinity;

            for (let k = i; k <= j - 1; k++) {
                q = m[`${i},${k}`] + m[`${k + 1},${j}`] + (p[i - 1] * p[k] * p[j]);

                if (q < m[`${i},${j}`]) {
                    m[`${i},${j}`] = q;
                    s[`${i},${j}`] = k;
                    console.log(`m[${i},${j}]=${m[`${i},${j}`]}`);
                }
            }
        }
    }

    return { m, s };
}

function printOptimalParens(s, i, j) {
    if (i === j) {
        return `A${i}`;
    } else {
        return `(${printOptimalParens(s, i, s[`${i},${j}`])}.${printOptimalParens(s, s[`${i},${j}`] + 1, j)})`;
    }
}

const { m, s } = matrixChainOrder([10, 20, 6, 24, 10, 100, 12]);

console.log(printOptimalParens(s, 1, 6));
