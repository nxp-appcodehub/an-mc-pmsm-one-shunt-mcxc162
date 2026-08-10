/*
 * Copyright 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "mcdrv_pwm3ph_epwm.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

static bool_t s_statusPass;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Function updates FTM value register
 *
 * @param this   Pointer to the current object
 *
 * @return none
 */
RAM_FUNC_LIB
void MCDRV_eFlexPwm3PhSet(mcdrv_pwm3ph_pwma_t *this)
{
    frac16_t f16ModuloTemp, f16FirstSampleEdge, f16SecondSampleEdge;
    GMCLIB_3COOR_T_F16 sUABCTemp;
    GMCLIB_3COOR_T_F16 sShiftTemp;

    /* pointer to duty cycle structure */
    sUABCTemp = *this->psUABC;
    sShiftTemp = *this->psShift;
    f16FirstSampleEdge = (*this).psSmplEdge->f16SmplFirstEdge;
    f16SecondSampleEdge = (*this).psSmplEdge->f16SmplSecondEdge;

    /* get modulo value from module 0 VAL1 register  */
    f16ModuloTemp = this->pui32PwmBaseAddress->SM[this->ui16PhASubNum].VAL1 + 1;

    /* phase A */
    this->i16OneShuntPhALeft = MLIB_Mul_F16(MLIB_SubSat_F16(sShiftTemp.f16A , sUABCTemp.f16A) , f16ModuloTemp);
    this->pui32PwmBaseAddress->SM[0].VAL2 = this->i16OneShuntPhALeft;
    this->pui32PwmBaseAddress->SM[0].VAL3 = MLIB_Mul_F16(MLIB_AddSat_F16(sShiftTemp.f16A , sUABCTemp.f16A) , f16ModuloTemp);

    /* phase B */
    this->i16OneShuntPhBLeft = MLIB_Mul_F16(MLIB_SubSat_F16(sShiftTemp.f16B , sUABCTemp.f16B) , f16ModuloTemp);
    this->pui32PwmBaseAddress->SM[1].VAL2 = this->i16OneShuntPhBLeft;
    this->pui32PwmBaseAddress->SM[1].VAL3 = MLIB_Mul_F16(MLIB_AddSat_F16(sShiftTemp.f16B , sUABCTemp.f16B) , f16ModuloTemp);

    /* phase C */
    this->i16OneShuntPhCLeft = MLIB_Mul_F16(MLIB_SubSat_F16(sShiftTemp.f16C , sUABCTemp.f16C) , f16ModuloTemp);
    this->pui32PwmBaseAddress->SM[2].VAL2 = this->i16OneShuntPhCLeft;
    this->pui32PwmBaseAddress->SM[2].VAL3 = MLIB_Mul_F16(MLIB_AddSat_F16(sShiftTemp.f16C , sUABCTemp.f16C) , f16ModuloTemp);

    /* Sample point update */
    this->i16OneShuntFirstSample = 	MLIB_Mul_F16(f16FirstSampleEdge,f16ModuloTemp)-this->ui16EdgeTuneFirst;
    this->i16OneShuntSecondSample = MLIB_Mul_F16(f16SecondSampleEdge,f16ModuloTemp)-this->ui16EdgeTuneSecond;
    this->pui32PwmBaseAddress->SM[0].VAL0 = this->i16OneShuntFirstSample;
    this->pui32PwmBaseAddress->SM[0].VAL4 = this->i16OneShuntSecondSample;

    /* set LDOK bits */
    this->pui32PwmBaseAddress->MCTRL |= PWM_MCTRL_LDOK_MASK;

}

/*!
 * @brief Function enables PWM outputs
 *
 * @param this   Pointer to the current object
 *
 * @return none
 */
void MCDRV_eFlexPwm3PhOutEn(mcdrv_pwm3ph_pwma_t *this)
{

    uint8_t ui8MaskTemp = 0U;

    ui8MaskTemp = (1U << (this->ui16PhASubNum)) | (1U << (this->ui16PhBSubNum)) | (1U << (this->ui16PhCSubNum));

    /* PWM outputs of sub-modules 0,1 and 2 enabled */
    /* PWM_A output */
    this->pui32PwmBaseAddress->OUTEN = (this->pui32PwmBaseAddress->OUTEN & ~(uint16_t)PWM_OUTEN_PWMA_EN_MASK) |
                                       PWM_OUTEN_PWMA_EN(ui8MaskTemp) | (this->pui32PwmBaseAddress->OUTEN);

    /* PWM_B output */
    this->pui32PwmBaseAddress->OUTEN = (this->pui32PwmBaseAddress->OUTEN & ~(uint16_t)PWM_OUTEN_PWMB_EN_MASK) |
                                       PWM_OUTEN_PWMB_EN(ui8MaskTemp) | (this->pui32PwmBaseAddress->OUTEN);

}

/*!
 * @brief Function disables PWM outputs
 *
 * @param this   Pointer to the current object
 *
 * @return none
 */
void MCDRV_eFlexPwm3PhOutDis(mcdrv_pwm3ph_pwma_t *this)
{

    uint32_t ui32MaskTemp  = 0U;
    uint16_t ui16PhSubTemp = 0U;

    ui16PhSubTemp = ~((1U << (this->ui16PhASubNum)) | (1U << (this->ui16PhBSubNum)) | (1U << (this->ui16PhCSubNum)));

    /* PWM outputs of used PWM sub-modules disabled */
    /* PWM_A output */
    ui32MaskTemp =
        ((this->pui32PwmBaseAddress->OUTEN & PWM_OUTEN_PWMA_EN_MASK) >> PWM_OUTEN_PWMA_EN_SHIFT) & ui16PhSubTemp;

    this->pui32PwmBaseAddress->OUTEN =
        (this->pui32PwmBaseAddress->OUTEN & ~(uint16_t)PWM_OUTEN_PWMA_EN_MASK) | PWM_OUTEN_PWMA_EN(ui32MaskTemp);

    /* PWM_B output */
    ui32MaskTemp =
        ((this->pui32PwmBaseAddress->OUTEN & PWM_OUTEN_PWMB_EN_MASK) >> PWM_OUTEN_PWMB_EN_SHIFT) & ui16PhSubTemp;

    this->pui32PwmBaseAddress->OUTEN =
        (this->pui32PwmBaseAddress->OUTEN & ~(uint16_t)PWM_OUTEN_PWMB_EN_MASK) | PWM_OUTEN_PWMB_EN(ui32MaskTemp);

}

/*!
 * @brief Function return actual value of over current flag
 *
 * @param this   Pointer to the current object
 *
 * @return boot_t true on success
 */
bool_t MCDRV_eFlexPwm3PhFltGet(mcdrv_pwm3ph_pwma_t *this)
{
   /* read over-current flags */
   s_statusPass = (((this->pui32PwmBaseAddress->FSTS & PWM_FSTS_FFPIN_MASK) >> 8) &
                   (1 << this->ui16FaultFixNum | 1 << this->ui16FaultAdjNum));

   /* clear faults flag */
   this->pui32PwmBaseAddress->FSTS = ((this->pui32PwmBaseAddress->FSTS & ~(uint16_t)(PWM_FSTS_FFLAG_MASK)) |
                                      (1 << this->ui16FaultFixNum | 1 << this->ui16FaultAdjNum));

    return ((s_statusPass > 0));
}

