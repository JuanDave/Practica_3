#include "ADC_init.h"
#include "fsl_adc16.h"
#include "MKL25Z4.h"

void ADC_init_channel(void){

	adc16_config_t ls_ADC_Cfg;
	ls_ADC_Cfg.referenceVoltageSource = kADC16_ReferenceVoltageSourceVref;
     ls_ADC_Cfg.clockSource = kADC16_ClockSourceAsynchronousClock;
     ls_ADC_Cfg.enableAsynchronousClock = false;
     ls_ADC_Cfg.clockDivider = kADC16_ClockDivider8;
     ls_ADC_Cfg.resolution = kADC16_ResolutionSE12Bit;
     ls_ADC_Cfg.longSampleMode = kADC16_LongSampleDisabled;
     ls_ADC_Cfg.enableHighSpeed = false;
     ls_ADC_Cfg.enableLowPower = false;
     ls_ADC_Cfg.enableContinuousConversion = true;
	 ADC16_Init(ADC0,&ls_ADC_Cfg);

	 adc16_channel_config_t adc_ChannelConfigStruct;
	 adc_ChannelConfigStruct.channelNumber = 0U;


#if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) && FSL_FEATURE_ADC16_HAS_CALIBRATION
    if (kStatus_Success == ADC16_DoAutoCalibration(ADC0))
    {
       /// PRINTF("\r\nADC16_DoAutoCalibration() Done.");
    }
    else
    {
      ///  PRINTF("ADC16_DoAutoCalibration() Failed.\r\n");
    }
#endif /* FSL_FEATURE_ADC16_HAS_CALIBRATION */

	 ADC16_SetChannelConfig(ADC0, 0U, &adc_ChannelConfigStruct);
}

