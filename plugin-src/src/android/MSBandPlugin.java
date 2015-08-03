import android.graphics.Bitmap;

import com.microsoft.band.BandClient;
import com.microsoft.band.BandClientManager;
import com.microsoft.band.BandException;
import com.microsoft.band.BandInfo;
import com.microsoft.band.*;
import com.microsoft.band.internal.device.subscription.AccelData;
import com.microsoft.band.internal.device.subscription.HeartRateData;
import com.microsoft.band.internal.device.subscription.UvData;
import com.microsoft.band.sensors.*;
import com.microsoft.band.ConnectionState;
import org.apache.cordova.CallbackContext;
import org.apache.cordova.*;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import com.microsoft.band.notifications.*;
import android.graphics.*;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.util.Collection;
import java.util.UUID;
import com.microsoft.band.tiles.BandIcon;
import com.microsoft.band.tiles.BandTile;
import java.util.Date;
import com.microsoft.band.notifications.MessageFlags;



public class MSBandPlugin extends CordovaPlugin {

    private BandClient bandClient;
    private BandHeartRateEventListener heartRateListener;
    private BandContactEventListener bandContactEventListener;
    private BandUVEventListener uvEventListener;
    private BandAccelerometerEventListener bandAccelerometerEventListener;


  public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {



    if (action.equals("connect")) {

      doConnect(callbackContext);

    }

    else if (action.equals("queryBandInfo"))
    {
      doqueryBandInfo(callbackContext);
    }

    else if (action.equals("watchSensor"))
    {
        dowatchSensor(callbackContext, args);
    }
    else if (action.equals("unwatchSensor"))
    {
        unwatchSensor(callbackContext, args);
    }
    else if (action.equals("vibrate"))
    {
        vibrateBand();
    }
    else if (action.equals("getRemainingTileCapacity"))
    {
        getRemainingTileCount(callbackContext);
    }

    else if (action.equals("addTile"))
    {
        addTileToBand(callbackContext, args);
    }
    else if (action.equals("removeTile"))
    {
        removeTileFromBand(callbackContext, args);
    }
    else if (action.equals("getCurrentTheme"))
    {
        getBandTheme(callbackContext);
    }
    else if (action.equals("setCurrentTheme"))
    {
        setBandTheme(callbackContext, args);
    }
    else if (action.equals("sendMesageWithTileId"))
    {
        sendMessageToTile(callbackContext, args);
    }
    else {
        return false;
    }
    return true;



}

    protected void doConnect(CallbackContext callbackContext) {
      BandInfo[] pairBands = BandClientManager.getInstance().getPairedBands();
        this.bandClient = BandClientManager.getInstance().create(cordova.getActivity(), pairBands[0]);

      BandPendingResult<ConnectionState> pendingResult =
      this.bandClient.connect();
      try {
        ConnectionState state = pendingResult.await();
           if(state == ConnectionState.CONNECTED) {

            callbackContext.success("");


           } else {
             PluginResult result = new PluginResult(PluginResult.Status.INVALID_ACTION, "");
             callbackContext.sendPluginResult(result);
           }
      } catch(InterruptedException ex) {
           // handle InterruptedException
      } catch(BandException ex) {
           // handle BandException
      }
    }


    protected void doqueryBandInfo(CallbackContext callbackContext) {
        if (this.bandClient.getConnectionState() == ConnectionState.CONNECTED)
        {
            String fwVersion = null;
        String hwVersion = null;
        try {

            BandPendingResult<ConnectionState> pendingResult =
                    this.bandClient.connect();
            pendingResult.await();


                BandPendingResult<String> pendingResultVersion = this.bandClient.getFirmwareVersion();
                fwVersion = pendingResultVersion.await();
                pendingResultVersion = this.bandClient.getHardwareVersion();

                hwVersion = pendingResultVersion.await();


                try {
                    JSONObject versionInfo = new JSONObject();
                    versionInfo.put("frameworkVersion", fwVersion);
                    versionInfo.put("hardwareVersion", hwVersion);

                    callbackContext.success(versionInfo);
                } catch (Exception ex) {

                }

            // do work related to Band firmware & hardware versions
        } catch (InterruptedException ex) {
            // handle InterruptedException
        } catch (BandIOException ex) {
            // handle BandIOException
        } catch (BandException ex) {
            // handle BandException
        }
    }
        else {
            PluginResult result = new PluginResult(PluginResult.Status.INVALID_ACTION, "");
            callbackContext.sendPluginResult(result);
        }

    }

    protected void vibrateBand()
    {
        try {

            // send a vibration request of type alert alarm to the Band using the following function call
            this.bandClient.getNotificationManager().vibrate(VibrationType.NOTIFICATION_ALARM).await();
            //another type of vibration
            this.bandClient.getNotificationManager().vibrate(VibrationType.RAMP_UP).await();
        }
        catch(Exception ex)
        {

        }
    }

    protected void getBandTheme(CallbackContext callbackContext)
    {
        if (this.bandClient.getConnectionState() == ConnectionState.CONNECTED) {
            try {

                BandTheme theme =
                        this.bandClient.getPersonalizationManager().getTheme().await();

                JSONObject objTheme = new JSONObject();




                objTheme.put("highLightColor", colorFromHex(theme.getHighlightColor()));
                objTheme.put("highContrastColor", colorFromHex(theme.getHighContrastColor()));
                objTheme.put("lowLightColor", colorFromHex(theme.getLowlightColor()));
                objTheme.put("secondaryTextColor", colorFromHex(theme.getSecondaryTextColor()));
                objTheme.put("mutedColor", colorFromHex(theme.getMutedColor()));
                objTheme.put("baseColor", colorFromHex(theme.getBaseColor()));

                callbackContext.success(objTheme);


            }
            catch (Exception ex) {
                  String msg = ex.getMessage();
            }
        }


    }

    protected void setBandTheme(CallbackContext callbackContext, JSONArray data)
    {
        if (this.bandClient.getConnectionState() == ConnectionState.CONNECTED) {
            try {

                int base = hexFromColor(data.getString(0));
                int highlight = hexFromColor(data.getString(1));
                int lowlight = hexFromColor(data.getString(2));
                int secondary = hexFromColor(data.getString(3));
                int highContrast = hexFromColor(data.getString(4));
                int muted = hexFromColor(data.getString(5));


                this.bandClient.getPersonalizationManager().setTheme(new
                        BandTheme(base, highlight, lowlight, secondary, highContrast,
                        muted)).await();


            } catch (Exception ex) {

            }
        }
        else
        {
            PluginResult result = new PluginResult(PluginResult.Status.INVALID_ACTION, "");
            callbackContext.sendPluginResult(result);

        }
    }

    protected void getRemainingTileCount(CallbackContext callbackContext)
    {
        if (this.bandClient.getConnectionState() == ConnectionState.CONNECTED) {


            try {

                // get remaining tile counts
                String remainingCapacity = this.bandClient.getTileManager().getRemainingTileCapacity().await().toString();
                JSONObject tileCapacity = new JSONObject();
                PluginResult res = new PluginResult(PluginResult.Status.OK, remainingCapacity);

                callbackContext.sendPluginResult(res);


            } catch (Exception ex) {

            }
        }
    }

    protected void addTileToBand(CallbackContext callbackContext, JSONArray data)
    {
        if (this.bandClient.getConnectionState() == ConnectionState.CONNECTED) {
            BandPendingResult<ConnectionState> pendingResult =
                    this.bandClient.connect();
            try {
                pendingResult.await();

//
                    UUID tileID = UUID.fromString(data.getString(0));
                    String tileName = data.getString(1);

                    File largeIconFile = new File(data.getString(2));
                     InputStream inputStream =this.cordova.getActivity().getAssets().open(data.getString(2));

                    Bitmap tileIcon = BitmapFactory.decodeStream(inputStream);

                    File smallIconFile = new File(data.getString(3));
                    InputStream inputStreamSmallIcon = this.cordova.getActivity().getAssets().open(data.getString(2));
                    Bitmap smallIconBitmap = BitmapFactory.decodeStream(inputStreamSmallIcon);
                //       Bitmap smallIconBitmap = Bitmap.createBitmap(24,24,null);
                    BandIcon smallIcon = BandIcon.toBandIcon(smallIconBitmap);




                    BandTile tile = new BandTile.Builder(tileID, tileName, tileIcon)
                            .setTileSmallIcon(smallIcon).build();

                    try {

                        if(this.bandClient.getTileManager().addTile(cordova.getActivity(), tile).await())
                        {
                              callbackContext.success("");
                        }

                    } catch (BandIOException e) {
                        // handle BandException
                    } catch (InterruptedException e) {
                        // handle InterruptedException
                    }


            } catch (Exception ex) {

            }
        }
    }

    protected void removeTileFromBand(CallbackContext callbackContext, JSONArray data)
    {
        if (this.bandClient.getConnectionState() == ConnectionState.CONNECTED) {
            BandPendingResult<ConnectionState> pendingResult =
                    this.bandClient.connect();
            try {
                pendingResult.await();


              //  Collection<BandTile> tiles = bandClient.getTileManager().getTiles().await();


                    UUID tileID = UUID.fromString(data.getString(0));

                    if (bandClient.getTileManager().removeTile(tileID).await()) {

                        PluginResult res = new PluginResult(PluginResult.Status.OK, "");
                        callbackContext.success(res);

                    }

            } catch (BandException e) {
                // handle BandException
            } catch (InterruptedException e) {
                // handle InterruptedException
            } catch (Exception ex) {

            }

        }
    }

    protected void sendMessageToTile(CallbackContext callbackContext, JSONArray data)
    {
        if(this.bandClient.getConnectionState() == ConnectionState.CONNECTED) {

            try {

                UUID tileID = UUID.fromString(data.getString(0));
                String title = data.getString(1);
                String body = data.getString(2);

                this.bandClient.getNotificationManager().sendMessage(tileID,title,body,new Date(),MessageFlags.SHOW_DIALOG).await();
            }

            catch(JSONException ex)
            {

            }
            catch (BandException ex)
            {

            }
            catch (InterruptedException ex)
            {

            }
    }
    }

    protected void dowatchSensor(final CallbackContext callbackContext,final JSONArray data) {
        if (this.bandClient.getConnectionState() == ConnectionState.CONNECTED) {

            try {

                switch (data.getString(0)) {
                    case "heartrate":
                        BandHeartRateEventListener heartRateListener = new
                                BandHeartRateEventListener() {
                                    @Override
                                    public void onBandHeartRateChanged(BandHeartRateEvent event) {

                                        int heartRate = event.getHeartRate();
                                        HeartRateQuality heartRateQuality = event.getQuality();
                                        int quality = heartRateQuality.ordinal();


                                        long timeStamp = event.getTimestamp();

                                        try {

                                            JSONObject reading = new JSONObject();
                                            reading.put("heartRate", heartRate);
                                            reading.put("quality", quality);
                                            reading.put("timestamp", timeStamp);
                                            JSONObject payload = new JSONObject();
                                            payload.put("event", "heartrate");
                                            payload.put("reading", reading);
                                            PluginResult res = new PluginResult(PluginResult.Status.OK, payload);
                                            res.setKeepCallback(true);
                                            callbackContext.sendPluginResult(res);
                                            //callbackContext.success(res);
                                        } catch (Exception ex) {

                                        }
                                    }
                                };

                        HeartRateConsentListener heartRateConsentListener = new HeartRateConsentListener() {
                            @Override
                            public void userAccepted(boolean b) {

                            }
                        };
                        if (this.bandClient.getSensorManager().getCurrentHeartRateConsent() != UserConsent.GRANTED) {
                            this.bandClient.getSensorManager().requestHeartRateConsent(this.cordova.getActivity(), heartRateConsentListener);

                        }
                        // register the listener

                        this.bandClient.getSensorManager().registerHeartRateEventListener(
                                heartRateListener);

                        break;

                    case "bandcontact":

                        BandContactEventListener bandContactEventListener = new BandContactEventListener() {
                            @Override
                            public void onBandContactChanged(BandContactEvent bandContactEvent) {

                                BandContactState bandContactState = bandContactEvent.getContactState();
                                int wornState = bandContactState.ordinal();
                                long timeStamp = bandContactEvent.getTimestamp();

                                try {

                                    JSONObject reading = new JSONObject();
                                    reading.put("wornState", wornState);
                                    reading.put("timestamp", timeStamp);
                                    JSONObject payload = new JSONObject();
                                    payload.put("event", "bandcontact");
                                    payload.put("reading", reading);
                                    PluginResult res = new PluginResult(PluginResult.Status.OK, payload);
                                    res.setKeepCallback(true);
                                    callbackContext.sendPluginResult(res);
                                    //callbackContext.success(res);
                                } catch (Exception ex) {

                                }

                            }
                        };
                         this.bandClient.getSensorManager().registerContactEventListener(bandContactEventListener);
                        break;

                    case "uvlevel":
                        BandUVEventListener uvEventListener = new BandUVEventListener() {
                            @Override
                            public void onBandUVChanged(BandUVEvent bandUVEvent) {


                                UVIndexLevel indexUV = bandUVEvent.getUVIndexLevel();
                                int uvLevel = indexUV.ordinal();

                                long timeStamp = bandUVEvent.getTimestamp();

                                try {

                                    JSONObject reading = new JSONObject();
                                    reading.put("uvIndexLevel", uvLevel);
                                    reading.put("timestamp", timeStamp);
                                    JSONObject payload = new JSONObject();
                                    payload.put("event", "uvlevel");
                                    payload.put("reading", reading);
                                    PluginResult res = new PluginResult(PluginResult.Status.OK, payload);
                                    res.setKeepCallback(true);
                                    callbackContext.sendPluginResult(res);
                                    //callbackContext.success(res);
                                } catch (Exception ex) {

                                }

                            }
                        };

                        this.bandClient.getSensorManager().registerUVEventListener(uvEventListener);
                        break;

                    case "accelerometer":

                        BandAccelerometerEventListener bandAccelerometerEventListener = new BandAccelerometerEventListener() {
                            @Override
                            public void onBandAccelerometerChanged(BandAccelerometerEvent bandAccelerometerEvent) {

                                float x = bandAccelerometerEvent.getAccelerationX();
                                float y = bandAccelerometerEvent.getAccelerationY();
                                float z = bandAccelerometerEvent.getAccelerationZ();

                                long timeStamp = bandAccelerometerEvent.getTimestamp();

                                try {

                                    JSONObject reading = new JSONObject();
                                    reading.put("x", x);
                                    reading.put("y", y);
                                    reading.put("z", z);
                                    reading.put("timestamp", timeStamp);
                                    JSONObject payload = new JSONObject();
                                    payload.put("event", "accelerometer");
                                    payload.put("reading", reading);
                                    PluginResult res = new PluginResult(PluginResult.Status.OK, payload);
                                    res.setKeepCallback(true);
                                    callbackContext.sendPluginResult(res);
                                    //callbackContext.success(res);
                                } catch (Exception ex) {

                                }
                            }
                        };
                            SampleRate sampleRate = SampleRate.MS128;
                            this.bandClient.getSensorManager().registerAccelerometerEventListener(bandAccelerometerEventListener,sampleRate);
                        break;

                    case "gyroscope":

                        BandGyroscopeEventListener bandGyroscopeEventListener = new BandGyroscopeEventListener() {
                            @Override
                            public void onBandGyroscopeChanged(BandGyroscopeEvent bandGyroscopeEvent) {

                                float x = bandGyroscopeEvent.getAngularVelocityX();
                                float y = bandGyroscopeEvent.getAngularVelocityY();
                                float z = bandGyroscopeEvent.getAngularVelocityZ();
                                long timeStamp = bandGyroscopeEvent.getTimestamp();

                                try {

                                    JSONObject reading = new JSONObject();
                                    reading.put("x", x);
                                    reading.put("y", y);
                                    reading.put("z", z);
                                    reading.put("timestamp", timeStamp);
                                    JSONObject payload = new JSONObject();
                                    payload.put("event", "gyroscope");
                                    payload.put("reading", reading);
                                    PluginResult res = new PluginResult(PluginResult.Status.OK, payload);
                                    res.setKeepCallback(true);
                                    callbackContext.sendPluginResult(res);
                                    //callbackContext.success(res);
                                } catch (Exception ex) {

                                }
                            }
                        };
                        SampleRate sampleRateGyroscope = SampleRate.MS128;
                        this.bandClient.getSensorManager().registerGyroscopeEventListener(bandGyroscopeEventListener, sampleRateGyroscope);
                        break;

                    case "distance":

                        BandDistanceEventListener distanceEventListener = new BandDistanceEventListener() {
                            @Override
                            public void onBandDistanceChanged(BandDistanceEvent bandDistanceEvent) {
                                long totalDistance = bandDistanceEvent.getTotalDistance();
                                float pace = bandDistanceEvent.getPace();
                                float speed = bandDistanceEvent.getSpeed();
                                MotionType motionType = bandDistanceEvent.getMotionType();
                                int pedometerMode = motionType.ordinal();
                                long timeStamp = bandDistanceEvent.getTimestamp();
                                try {

                                    JSONObject reading = new JSONObject();
                                    reading.put("totalDistance", totalDistance);
                                    reading.put("speed", speed);
                                    reading.put("pace", pace);
                                    reading.put("pedometerMode", pedometerMode);
                                    reading.put("timestamp", timeStamp);
                                    JSONObject payload = new JSONObject();
                                    payload.put("event", "distance");
                                    payload.put("reading", reading);
                                    PluginResult res = new PluginResult(PluginResult.Status.OK, payload);
                                    res.setKeepCallback(true);
                                    callbackContext.sendPluginResult(res);
                                    //callbackContext.success(res);
                                } catch (Exception ex) {

                                }

                            }
                        };
                        this.bandClient.getSensorManager().registerDistanceEventListener(distanceEventListener);
                        break;

                    case "skintemperature":

                        BandSkinTemperatureEventListener skinTemperatureEventListener = new BandSkinTemperatureEventListener() {
                            @Override
                            public void onBandSkinTemperatureChanged(BandSkinTemperatureEvent bandSkinTemperatureEvent) {

                                float temperature =  bandSkinTemperatureEvent.getTemperature();
                                long timeStamp = bandSkinTemperatureEvent.getTimestamp();

                                try {

                                    JSONObject reading = new JSONObject();

                                    reading.put("temperature", temperature);
                                    reading.put("timestamp", timeStamp);
                                    JSONObject payload = new JSONObject();
                                    payload.put("event", "skintemperature");
                                    payload.put("reading", reading);
                                    PluginResult res = new PluginResult(PluginResult.Status.OK, payload);
                                    res.setKeepCallback(true);
                                    callbackContext.sendPluginResult(res);
                                    //callbackContext.success(res);
                                } catch (Exception ex) {

                                }
                            }
                        };
                        this.bandClient.getSensorManager().registerSkinTemperatureEventListener(skinTemperatureEventListener);
                        break;

                    case "pedometer":

                        BandPedometerEventListener bandPedometerEventListener = new BandPedometerEventListener() {
                            @Override
                            public void onBandPedometerChanged(BandPedometerEvent bandPedometerEvent) {

                                long totalSteps = bandPedometerEvent.getTotalSteps();
                                long timeStamp = bandPedometerEvent.getTimestamp();
                                try {

                                    JSONObject reading = new JSONObject();

                                    reading.put("totalSteps", totalSteps);
                                    reading.put("timestamp", timeStamp);
                                    JSONObject payload = new JSONObject();
                                    payload.put("event", "pedometer");
                                    payload.put("reading", reading);
                                    PluginResult res = new PluginResult(PluginResult.Status.OK, payload);
                                    res.setKeepCallback(true);
                                    callbackContext.sendPluginResult(res);
                                    //callbackContext.success(res);
                                } catch (Exception ex) {

                                }
                            }
                        };
                        this.bandClient.getSensorManager().registerPedometerEventListener(bandPedometerEventListener);
                        break;

                }



        } catch (BandException ex) {
            // handle BandException
        }
        catch (JSONException ex)
        {

        }

    }}
    protected void unwatchSensor(CallbackContext callbackContext, JSONArray data) {

        if (this.bandClient.getConnectionState() == ConnectionState.CONNECTED) {

            try {

                switch (data.getString(0)) {
                    case "heartrate":
                        this.bandClient.getSensorManager().unregisterHeartRateEventListeners();
                        break;
                    case "bandcontact":
                        this.bandClient.getSensorManager().unregisterContactEventListeners();
                        break;
                    case "accelerometer":
                        this.bandClient.getSensorManager().unregisterAccelerometerEventListeners();
                        break;
                    case "gyroscope":
                        this.bandClient.getSensorManager().unregisterGyroscopeEventListeners();
                        break;
                    case "distance":
                        this.bandClient.getSensorManager().unregisterDistanceEventListeners();
                        break;
                    case "pedometer":
                        this.bandClient.getSensorManager().unregisterPedometerEventListeners();
                        break;
                    case "skintemperature":
                        this.bandClient.getSensorManager().unregisterSkinTemperatureEventListeners();
                        break;
                    case "uvlevel":
                        this.bandClient.getSensorManager().unregisterUVEventListeners();
                        break;

                }

            } catch (BandException ex) {
                // handle BandException
            }
            catch (JSONException ex) {
                // handle BandException
            }
        }
    }

    protected String colorFromHex (int hex)
    {
        String hexColor = String.format("#%06X", (0xFFFFFF & hex));
        return  hexColor;
    }

    protected int hexFromColor (String color )
    {
        int hexColor = Integer.parseInt(color.replaceFirst("#", ""), 16);

        return hexColor;
    }
  }
