const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");
const histogramCanvas = document.getElementById("histogramCanvas");
const histogramCtx = histogramCanvas.getContext("2d");
let img = new Image();

document.getElementById("imageInput").addEventListener("change", (e) => {
  const file = e.target.files[0];
  if (file) {
    const reader = new FileReader();
    reader.onload = (e) => {
      img.src = e.target.result;
    };
    reader.readAsDataURL(file);
  }
});

img.onload = () => {
  canvas.width = img.width;
  canvas.height = img.height;
  ctx.drawImage(img, 0, 0);
  drawHistogram();
};

document.getElementById("solarizeButton").addEventListener("click", () => {
  solarize();
  drawHistogram();
});

document.getElementById("embossButton").addEventListener("click", () => {
  emboss();
  drawHistogram();
});

document.getElementById("saveButton").addEventListener("click", () => {
  const link = document.createElement("a");
  link.href = canvas.toDataURL("image/png");
  link.download = "processed_image.png";
  link.click();
});

document.getElementById("resetButton").addEventListener("click", () => {
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  ctx.drawImage(img, 0, 0);
  drawHistogram();

  document.getElementById("contrastSlider").value = 100;
  document.getElementById("brightnessSlider").value = 100;
});

document.getElementById("contrastSlider").addEventListener("input", (e) => {
  applyAdjustments();
});

document.getElementById("brightnessSlider").addEventListener("input", (e) => {
  applyAdjustments();
});

function drawHistogram() {
  const imageData = ctx.getImageData(0, 0, canvas.width, canvas.height);
  const data = imageData.data;
  const histogram = new Array(256).fill(0);

  for (let i = 0; i < data.length; i += 4) {
    const brightness = Math.round(
      0.299 * data[i] + 0.587 * data[i + 1] + 0.114 * data[i + 2]
    );
    histogram[brightness]++;
  }

  const max = Math.max(...histogram);

  histogramCanvas.width = 256;
  histogramCanvas.height = 100;

  histogramCtx.clearRect(0, 0, 256, 100);

  for (let i = 0; i < 256; i++) {
    const height = histogram[i] * (histogramCanvas.height / max);
    histogramCtx.fillRect(i, histogramCanvas.height - height, 1, height);
  }
}

function solarize() {
  const imageData = ctx.getImageData(0, 0, canvas.width, canvas.height);
  const data = imageData.data;
  for (let i = 0; i < data.length; i += 4) {
    data[i] = 0.5 * (255 - data[i]);
    data[i + 1] = 0.5 * (255 - data[i + 1]);
    data[i + 2] = 0.5 * (255 - data[i + 2]);
  }
  ctx.putImageData(imageData, 0, 0);
}

function emboss() {
  const imageData = ctx.getImageData(0, 0, canvas.width, canvas.height);
  const data = imageData.data;
  const width = imageData.width;
  const height = imageData.height;

  const embossKernel = [
    [-2, -1, 0],
    [-1, 1, 1],
    [0, 1, 2],
  ];

  const outputData = new ImageData(width, height);

  for (let y = 1; y < height - 1; y++) {
    for (let x = 1; x < width - 1; x++) {
      let r = 0,
        g = 0,
        b = 0;
      for (let ky = -1; ky <= 1; ky++) {
        for (let kx = -1; kx <= 1; kx++) {
          const pixelIndex = ((y + ky) * width + (x + kx)) * 4;
          r += data[pixelIndex] * embossKernel[ky + 1][kx + 1];
          g += data[pixelIndex + 1] * embossKernel[ky + 1][kx + 1];
          b += data[pixelIndex + 2] * embossKernel[ky + 1][kx + 1];
        }
      }

      const newPixelIndex = (y * width + x) * 4;
      outputData.data[newPixelIndex] = r;
      outputData.data[newPixelIndex + 1] = g;
      outputData.data[newPixelIndex + 2] = b;
      outputData.data[newPixelIndex + 3] = 255;
    }
  }

  ctx.putImageData(outputData, 0, 0);
}

function applyAdjustments() {
  const contrast = document.getElementById("contrastSlider").value;
  const brightness = document.getElementById("brightnessSlider").value;

  ctx.clearRect(0, 0, canvas.width, canvas.height);
  ctx.drawImage(img, 0, 0);

  const imageData = ctx.getImageData(0, 0, canvas.width, canvas.height);
  const data = imageData.data;

  for (let i = 0; i < data.length; i += 4) {
    data[i] = (data[i] - 128) * (contrast / 100) + 128 + (brightness - 100); // R
    data[i + 1] =
      (data[i + 1] - 128) * (contrast / 100) + 128 + (brightness - 100); // G
    data[i + 2] =
      (data[i + 2] - 128) * (contrast / 100) + 128 + (brightness - 100); // B
  }

  ctx.putImageData(imageData, 0, 0);
  drawHistogram();
}
