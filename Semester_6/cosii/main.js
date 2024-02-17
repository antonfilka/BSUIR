// Функция для вычисления ДПФ
function dft(x) {
  const N = x.length;
  const X = [];

  for (let k = 0; k < N; k++) {
    let re = 0;
    let im = 0;

    for (let n = 0; n < N; n++) {
      const phi = (2 * Math.PI * k * n) / N;
      re += x[n] * Math.cos(phi);
      im -= x[n] * Math.sin(phi);
    }

    X[k] = { re, im };
  }

  return X;
}

// Функция для вычисления БПФ с прореживанием по времени N=8
function fft(x) {
  const N = x.length;

  if (N === 1) {
    return x;
  }

  if (N % 2 !== 0) {
    throw new Error("Размер массива должен быть степенью двойки.");
  }

  const X_even = fft(x.filter((_, i) => i % 2 === 0));
  const X_odd = fft(x.filter((_, i) => i % 2 !== 0));

  const X = [];

  for (let k = 0; k < N; k++) {
    const phi = (-2 * Math.PI * k) / N;
    const exp = { re: Math.cos(phi), im: Math.sin(phi) };
    const term = {
      re: exp.re * X_odd[k / 2].re - exp.im * X_odd[k / 2].im,
      im: exp.re * X_odd[k / 2].im + exp.im * X_odd[k / 2].re,
    };
    X[k] = {
      re: X_even[k].re + term.re,
      im: X_even[k].im + term.im,
    };
    X[k + N / 2] = {
      re: X_even[k].re - term.re,
      im: X_even[k].im - term.im,
    };
  }

  return X;
}

// Функция для вычисления обратного БПФ
function ifft(X) {
  const N = X.length;

  // Сопряженно-комплексное отображение входных данных
  X = X.map((x) => ({ re: x.re, im: -x.im }));

  // Вычисление БПФ
  const x = fft(X);

  // Сопряженно-комплексное отображение результата и масштабирование
  return x.map((x) => ({ re: x.re / N, im: -x.im / N }));
}

// Пример использования
const x = [1, 2, 3, 4, 5, 6, 7, 8];

console.log(dft(x));
console.log(fft(x));
console.log(ifft(x));
