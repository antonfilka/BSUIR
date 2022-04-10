import React, { useState } from "react";
import styles from "./Lab1.module.css";
import axios from "axios";

const Lab1 = () => {
  const [toShift, setToShift] = useState("");
  const [toUnShift, setToUnShift] = useState("");

  const [shifted, setShifted] = useState("");
  const [unShifted, setUnShifted] = useState("");

  const handlerShift = (text) => {
    axios
      .get(`http://localhost:8080/api/text/shift?text=${text}`, {
        headers: {
          "Access-Control-Allow-Origin": "*",
        },
      })
      .then((res) => {
        const response = res.data.shiftedText;
        setShifted(response);
      });
  };

  const handlerUnShift = (text) => {
    axios
      .get(`http://localhost:8080/api/text/unshift?text=${text}`, {
        headers: {
          "Access-Control-Allow-Origin": "*",
        },
      })
      .then((res) => {
        const response = res.data.unShiftedText;
        setUnShifted(response);
      });
  };

  return (
    <div className={styles.lab}>
      <div className={styles.T1}>Lab 1</div>
      <div className={styles.line}>
        <label>Non shifted text</label>
        <input onChange={(e) => setToShift(e.target.value)} />
        <label>Shifted text:</label>
        <div className={styles.result}> {shifted}</div>
        <button onClick={() => handlerShift(toShift)}>Shift</button>
      </div>
      <div className={styles.line}>
        <label>Shifted text</label>
        <input onChange={(e) => setToUnShift(e.target.value)} />
        <label>UnShifted text:</label>
        <div className={styles.result}> {unShifted}</div>
        <button onClick={() => handlerUnShift(toUnShift)}>UnShift</button>
      </div>
    </div>
  );
};

export default Lab1;
