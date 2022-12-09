document.getElementById("convert").addEventListener("click", function (event) {
  let inputStr = document.getElementById("input").value;
  inputStr = inputStr.split("");
  const transOption = document.getElementById("transOption").value;

  if (transOption == "Bit Stuffing") {
    bitStuffing(inputStr);
  } else if (transOption == "Bit De Stuffing") {
    bitDeStuffing(inputStr);
  }
});

const bitStuffing = (inputStr) => {
  let bitsLength = inputStr.length;
  let count = 0;
  for (let i = 0; i < bitsLength; i++) {
    if (inputStr[i] === "1") {
      count += 1;
    } else {
      count = 0;
    }

    if (count == 5) {
      for (let j = bitsLength; j > i; j--) {
        inputStr[j] = inputStr[j - 1];
      }
      inputStr[i + 1] = "0";
      bitsLength += 1;
      count = 0;
    }
  }
  inputStr = inputStr.join("");
  document.getElementById("output").value = inputStr;
};

const bitDeStuffing = (inputStr) => {
  let bitsLength = inputStr.length;
  let count = 0;
  for (let i = 0; i < bitsLength; i++) {
    if (inputStr[i] === "1") {
      count += 1;
    } else {
      count = 0;
    }

    if (count == 5) {
      for (let j = i + 1; j < bitsLength; j++) {
        inputStr[j] = inputStr[j + 1];
      }
      bitsLength -= 1;
      count = 0;
    }
  }
  inputStr = inputStr.join("");
  document.getElementById("output").value = inputStr;
};

const flag = "z";
const esc = "m";

function byteStuffing(inputStr) {
  const stringLength = inputStr.length;
  let stuffed = [];

  let count = 0;
  for (let i = 0; i < stringLength; i++, count++) {
    if (inputStr[i] === flag || inputStr[i] === esc) {
      stuffed[count] = esc;
      count++;
      stuffed[count] = inputStr[i];
    } else {
      stuffed[count] = inputStr[i];
    }
  }
  inputStr = stuffed.join("");
  document.getElementById("output").value = inputStr;
}

function byteDeStuffing(inputStr) {
  const stringLength = inputStr.length;
  for (let i = 0; i < stringLength; i++) {
    if (
      inputStr[i] == esc &&
      (inputStr[i + 1] == esc || inputStr[i + 1] == flag)
    ) {
      inputStr.splice(i, 1);
    }
  }
  inputStr = inputStr.join("");
  document.getElementById("output").value = inputStr;
}
