// const schemas            = ["Thing"];
const schemas            = ["Action", "AchieveAction", "LoseAction", "TieAction", "WinAction", "AssessAction", "ChooseAction", "IgnoreAction", "ReactAction", "ReviewAction", "ConsumeAction", "DrinkAction", "EatAction", "InstallAction", "ListenAction", "PlayGameAction", "ReadAction", "UseAction", "ViewAction", "WatchAction", "ControlAction", "ActivateAction", "DeactivateAction", "ResumeAction", "SuspendAction", "CreateAction", "CookAction", "DrawAction", "FilmAction", "PaintAction", "PhotographAction", "WriteAction", "FindAction", "CheckAction", "DiscoverAction", "TrackAction", "InteractAction", "BefriendAction", "CommunicateAction", "FollowAction", "JoinAction", "LeaveAction", "MarryAction", "RegisterAction", "SubscribeAction", "UnRegisterAction", "MoveAction", "ArriveAction", "DepartAction", "TravelAction", "OrganizeAction", "AllocateAction", "AcceptAction", "AssignAction", "AuthorizeAction", "RejectAction", "ApplyAction", "BookmarkAction", "PlanAction", "CancelAction", "ReserveAction", "ScheduleAction", "PlayAction", "ExerciseAction", "PerformAction", "SearchAction", "SeekToAction", "SolveMathAction", "TradeAction", "BuyAction", "DonateAction", "OrderAction", "PayAction", "PreOrderAction", "QuoteAction", "RentAction", "SellAction", "TipAction", "TransferAction", "BorrowAction", "DownloadAction", "GiveAction", "LendAction", "MoneyTransfer", "ReceiveAction", "ReturnAction", "SendAction", "TakeAction", "UpdateAction", "AddAction", "InsertAction", "AppendAction", "PrependAction", "DeleteAction", "ReplaceAction", "BioChemEntity", "ChemicalSubstance", "Gene", "MolecularEntity", "Protein", "CreativeWork", "AmpStory", "ArchiveComponent", "Article", "AdvertiserContentArticle", "NewsArticle", "AnalysisNewsArticle", "AskPublicNewsArticle", "BackgroundNewsArticle", "OpinionNewsArticle", "ReportageNewsArticle", "ReviewNewsArticle", "Report", "SatiricalArticle", "ScholarlyArticle", "MedicalScholarlyArticle", "SocialMediaPosting", "BlogPosting", "LiveBlogPosting", "DiscussionForumPosting", "TechArticle", "APIReference", "Atlas", "Blog", "Book", "AudioBook", "Chapter", "Claim", "Clip", "MovieClip", "RadioClip", "TVClip", "VideoGameClip", "Collection", "ProductCollection", "ComicStory", "ComicCoverArt", "Comment", "Answer", "CorrectionComment", "Question", "Conversation", "Course", "CreativeWorkSeason", "PodcastSeason", "RadioSeason", "TVSeason", "CreativeWorkSeries", "BookSeries", "MovieSeries", "PodcastSeries", "RadioSeries", "TVSeries", "VideoGameSeries", "DataCatalog", "Dataset", "DataFeed", "CompleteDataFeed", "DefinedTermSet", "CategoryCodeSet", "Diet", "DigitalDocument", "NoteDigitalDocument", "PresentationDigitalDocument", "SpreadsheetDigitalDocument", "TextDigitalDocument", "Drawing", "EducationalOccupationalCredential", "Episode", "PodcastEpisode", "RadioEpisode", "TVEpisode", "ExercisePlan", "Game", "VideoGame", "Guide", "HowTo", "Recipe", "HowToDirection", "HowToSection", "HowToStep", "HowToTip", "HyperToc", "HyperTocEntry", "LearningResource", "Course", "Quiz", "Legislation", "LegislationObject", "Manuscript", "Map", "MathSolver", "MediaObject", "3DModel", "AmpStory", "AudioObject", "DataDownload", "ImageObject", "Barcode", "ImageObjectSnapshot", "LegislationObject", "MusicVideoObject", "VideoObject", "VideoObjectSnapshot", "MediaReviewItem", "Menu", "MenuSection", "Message", "EmailMessage", "Movie", "MusicComposition", "MusicPlaylist", "MusicAlbum", "MusicRelease", "MusicRecording", "Painting", "Photograph", "Play", "Poster", "PublicationIssue", "ComicIssue", "PublicationVolume", "Quotation", "Review", "ClaimReview", "CriticReview", "ReviewNewsArticle", "EmployerReview", "MediaReview", "Recommendation", "UserReview", "Sculpture", "SheetMusic", "ShortStory", "SoftwareApplication", "MobileApplication", "VideoGame", "WebApplication", "SoftwareSourceCode", "SpecialAnnouncement", "Statement", "TVSeason", "TVSeries", "Thesis", "VisualArtwork", "CoverArt", "ComicCoverArt", "WebContent", "HealthTopicContent", "WebPage", "AboutPage", "CheckoutPage", "CollectionPage", "MediaGallery", "ImageGallery", "VideoGallery", "ContactPage", "FAQPage", "ItemPage", "MedicalWebPage", "ProfilePage", "QAPage", "RealEstateListing", "SearchResultsPage", "WebPageElement", "SiteNavigationElement", "Table", "WPAdBlock", "WPFooter", "WPHeader", "WPSideBar", "WebSite", "Event", "BusinessEvent", "ChildrensEvent", "ComedyEvent", "CourseInstance", "DanceEvent", "DeliveryEvent", "EducationEvent", "EventSeries", "ExhibitionEvent", "Festival", "FoodEvent", "Hackathon", "LiteraryEvent", "MusicEvent", "PublicationEvent", "BroadcastEvent", "OnDemandEvent", "SaleEvent", "ScreeningEvent", "SocialEvent", "SportsEvent", "TheaterEvent", "VisualArtsEvent", "Intangible", "ActionAccessSpecification", "AlignmentObject", "Audience", "BusinessAudience", "EducationalAudience", "MedicalAudience", "Patient", "PeopleAudience", "MedicalAudience", "Patient", "ParentAudience", "Researcher", "BedDetails", "Brand", "BroadcastChannel", "RadioChannel", "AMRadioChannel", "FMRadioChannel", "TelevisionChannel", "BroadcastFrequencySpecification", "Class", "ComputerLanguage", "DataFeedItem", "DefinedTerm", "CategoryCode", "MedicalCode", "Demand", "DigitalDocumentPermission", "EducationalOccupationalProgram", "WorkBasedProgram", "EnergyConsumptionDetails", "EntryPoint", "Enumeration", "AdultOrientedEnumeration", "BoardingPolicyType", "BookFormatType", "BusinessEntityType", "BusinessFunction", "CarUsageType", "ContactPointOption", "DayOfWeek", "DeliveryMethod", "DigitalDocumentPermissionType", "DigitalPlatformEnumeration", "EnergyEfficiencyEnumeration", "EUEnergyEfficiencyEnumeration", "EnergyStarEnergyEfficiencyEnumeration", "EventAttendanceModeEnumeration", "GameAvailabilityEnumeration", "GamePlayMode", "GenderType", "GovernmentBenefitsType", "HealthAspectEnumeration", "BodyMeasurementTypeEnumeration", "WearableMeasurementTypeEnumeration", "ItemAvailability", "ItemListOrderType", "LegalValueLevel", "MapCategoryType", "MeasurementTypeEnumeration", "MediaManipulationRatingEnumeration", "MedicalEnumeration", "DrugCostCategory", "DrugPregnancyCategory", "DrugPrescriptionStatus", "InfectiousAgentClass", "MedicalAudienceType", "MedicalDevicePurpose", "MedicalEvidenceLevel", "MedicalImagingTechnique", "MedicalObservationalStudyDesign", "MedicalProcedureType", "MedicalSpecialty", "MedicalStudyStatus", "MedicalTrialDesign", "MedicineSystem", "PhysicalExam", "MerchantReturnEnumeration", "MusicAlbumProductionType", "MusicAlbumReleaseType", "MusicReleaseFormatType", "NonprofitType", "NLNonprofitType", "UKNonprofitType", "USNonprofitType", "OfferItemCondition", "PaymentMethod", "PaymentCard", "CreditCard", "PhysicalActivityCategory", "PriceComponentTypeEnumeration", "PriceTypeEnumeration", "QualitativeValue", "BedType", "DriveWheelConfigurationValue", "SizeSpecification", "SteeringPositionValue", "RefundTypeEnumeration", "RestrictedDiet", "ReturnFeesEnumeration", "ReturnLabelSourceEnumeration", "ReturnMethodEnumeration", "RsvpResponseType", "SizeGroupEnumeration", "WearableSizeGroupEnumeration", "SizeSystemEnumeration", "WearableSizeSystemEnumeration", "Specialty", "MedicalSpecialty", "StatusEnumeration", "ActionStatusType", "EventStatusType", "GameServerStatus", "LegalForceStatus", "OrderStatus", "PaymentStatusType", "ReservationStatusType", "WarrantyScope", "FloorPlan", "GameServer", "GeospatialGeometry", "Grant", "MonetaryGrant", "HealthInsurancePlan", "HealthPlanCostSharingSpecification", "HealthPlanFormulary", "HealthPlanNetwork", "Invoice", "ItemList", "BreadcrumbList", "HowToSection", "HowToStep", "OfferCatalog", "JobPosting", "Language", "ListItem", "HowToDirection", "HowToItem", "HowToSupply", "HowToTool", "HowToSection", "HowToStep", "HowToTip", "MediaSubscription", "MenuItem", "MerchantReturnPolicy", "MerchantReturnPolicySeasonalOverride", "Observation", "Occupation", "OccupationalExperienceRequirements", "Offer", "AggregateOffer", "OfferForLease", "OfferForPurchase", "Order", "OrderItem", "ParcelDelivery", "Permit", "GovernmentPermit", "ProgramMembership", "Property", "PropertyValueSpecification", "Quantity", "Distance", "Duration", "Energy", "Mass", "Rating", "AggregateRating", "EmployerAggregateRating", "EndorsementRating", "Reservation", "BoatReservation", "BusReservation", "EventReservation", "FlightReservation", "FoodEstablishmentReservation", "LodgingReservation", "RentalCarReservation", "ReservationPackage", "TaxiReservation", "TrainReservation", "Role", "LinkRole", "OrganizationRole", "EmployeeRole", "PerformanceRole", "Schedule", "Seat", "Series", "CreativeWorkSeries", "BookSeries", "MovieSeries", "PodcastSeries", "RadioSeries", "TVSeries", "VideoGameSeries", "EventSeries", "Service", "BroadcastService", "RadioBroadcastService", "CableOrSatelliteService", "FinancialProduct", "BankAccount", "DepositAccount", "CurrencyConversionService", "InvestmentOrDeposit", "BrokerageAccount", "DepositAccount", "InvestmentFund", "LoanOrCredit", "CreditCard", "MortgageLoan", "PaymentCard", "CreditCard", "PaymentService", "FoodService", "GovernmentService", "TaxiService", "WebAPI", "ServiceChannel", "SpeakableSpecification", "StatisticalPopulation", "StructuredValue", "CDCPMDRecord", "ContactPoint", "PostalAddress", "DefinedRegion", "DeliveryTimeSettings", "EngineSpecification", "ExchangeRateSpecification", "GeoCoordinates", "GeoShape", "GeoCircle", "InteractionCounter", "MonetaryAmount", "NutritionInformation", "OfferShippingDetails", "OpeningHoursSpecification", "OwnershipInfo", "PostalCodeRangeSpecification", "PriceSpecification", "CompoundPriceSpecification", "DeliveryChargeSpecification", "PaymentChargeSpecification", "UnitPriceSpecification", "PropertyValue", "LocationFeatureSpecification", "QuantitativeValue", "QuantitativeValueDistribution", "MonetaryAmountDistribution", "RepaymentSpecification", "ShippingDeliveryTime", "ShippingRateSettings", "TypeAndQuantityNode", "WarrantyPromise", "Ticket", "Trip", "BoatTrip", "BusTrip", "Flight", "TouristTrip", "TrainTrip", "VirtualLocation", "MedicalEntity", "AnatomicalStructure", "Bone", "BrainStructure", "Joint", "Ligament", "Muscle", "Nerve", "Vessel", "Artery", "LymphaticVessel", "Vein", "AnatomicalSystem", "DrugClass", "DrugCost", "LifestyleModification", "Diet", "PhysicalActivity", "ExercisePlan", "MedicalCause", "MedicalCondition", "InfectiousDisease", "MedicalSignOrSympyom", "MedicalSign", "VitalSign", "MedicalSymptom", "MedicalContraindication", "MedicalDevice", "MedicalGuideline", "MedicalGuidelineContraindication", "MedicalGuidelineRecommendation", "MedicalIndication", "ApprovedIndication", "PreventionIndication", "TreatmentIndication", "MedicalIntangible", "DDxElement", "DoseSchedule", "MaximumDoseSchedule", "RecommendedDoseSchedule", "ReportedDoseSchedule", "DrugLegalStatus", "DrugStrength", "MedicalCode", "MedicalConditionStage", "MedicalProcedure", "DiagnosticProcedure", "PalliativeProcedure", "PhysicalExam", "SurgicalProcedure", "TherapeuticProcedure", "MedicalTherapy", "OccupationalTherapy", "PalliativeProcedure", "PhysicalTherapy", "RadiationTherapy", "RespiratoryTherapy", "PsychologicalTreatment", "MedicalRiskEstimator", "MedicalRiskCalculator", "MedicalRiskScore", "MedicalRiskFactor", "MedicalStudy", "MedicalObservationalStudy", "MedicalTrial", "MedicalTest", "BloodTest", "ImagingTest", "MedicalTestPanel", "PathologyTest", "Substance", "DietarySupplment", "Drug", "SuperficialAnatomy", "Organization", "Airline", "Consortium", "Corporation", "EducationalOrganization", "CollegeOrUniversity", "ElementarySchool", "HighSchool", "MiddleSchool", "Preschool", "School", "FundingScheme", "GovernmentOrganization", "LibrarySystem", "LocalBusiness", "AnimalShelter", "ArchiveOrganization", "AutomotiveBusiness", "AutoBodyShop", "AutoDealer", "AutoPartsStore", "AutoRental", "AutoRepair", "AutoWash", "GasStation", "MotorcycleDealer", "MotorcycleRepair", "ChildCare", "Dentist", "DryCleaningOrLaundry", "EmergencyService", "FireStation", "Hospital", "PoliceStation", "EmploymentAgency", "EntertainmentBusiness", "AdultEntertainment", "AmusementPark", "ArtGallery", "Casino", "ComedyClub", "MovieTheater", "NightClub", "FinancialService", "AccountingService", "AutomatedTeller", "BankOrCreditUnion", "InsuranceAgency", "FoodEstablishment", "Bakery", "BarOrPub", "Brewery", "CafeOrCoffeeShop", "Distillery", "FastFoodRestaurant", "IceCreamShop", "Restaurant", "Winery", "GovernmentOffice", "PostOffice", "HealthAndBeautyBusiness", "BeautySalon", "DaySpa", "HairSalon", "HealthClub", "NailSalon", "TattooParlor", "HomeAndConstructionBusiness", "Electrician", "GeneralContractor", "HVACBusiness", "HousePainter", "Locksmith", "MovingCompany", "Plumber", "RoofingConstructor", "InternetCafe", "LegalService", "Attorney", "Notary", "Library", "LodgingBusiness", "BedAndBreakfast", "Campground", "Hostel", "Hotel", "Motel", "Resort", "SkiResort", "MedicalBusiness", "CommunityHealth", "Dentist", "Dermatology", "DietNutrition", "Emergency", "Geriatric", "Gynecologic", "MedicalClinic", "CovidTestingFacility", "Midwifery", "Nursing", "Obstetric", "Oncologic", "Optician", "Optometric", "Otolaryngologic", "Pediatric", "Pharmacy", "Physician", "PlasticSurgery", "Podiatric", "PrimaryCare", "Psychiatric", "PublicHealth", "ProfessionalService", "RadioStation", "RealEstateAgent", "RecyclingCenter", "SelfStorage", "ShoppingCenter", "SportsActivityLocation", "BowlingAlley", "ExerciseGym", "GolfCourse", "HealthClub", "PublicSwimmingPool", "SkiResort", "SportsClub", "StadiumOrArena", "TennisComplex", "Store", "AutoPartsStore", "BikeStore", "BookStore", "ClothingStore", "ComputerStore", "ConvenienceStore", "DepartmentStore", "ElectronicsStore", "Florist", "FurnitureStore", "GardenStore", "GroceryStore", "HardwareStore", "HobbyShop", "HomeGoodsStore", "JewelryStore", "LiquorStore", "MensClothingStore", "MobilePhoneStore", "MovieRentalStore", "MusicStore", "OfficeEquipmentStore", "OutletStore", "PawnShop", "PetStore", "ShoeStore", "SportingGoodsStore", "TireShop", "ToyStore", "WholesaleStore", "TelevisionStation", "TouristInformationCenter", "TravelAgency", "MedicalOrganization", "Dentist", "DiagnosticLab", "Hospital", "MedicalClinic", "CovidTestingFacility", "Pharmacy", "Physician", "VeterinaryCare", "NGO", "NewsMediaOrganization", "OnlineBusiness", "OnlineStore", "PerformingGroup", "DanceGroup", "MusicGroup", "TheaterGroup", "Project", "FundingAgency", "ResearchProject", "ResearchOrganization", "SearchRescueOrganization", "SportsOrganization", "SportsTeam", "WorkersUnion", "Person", "Patient", "Place", "Accommodation", "Apartment", "CampingPitch", "House", "SingleFamilyResidence", "Room", "HotelRoom", "MeetingRoom", "Suite", "AdministrativeArea", "City", "Country", "SchoolDistrict", "State", "CivicStructure", "Airport", "Aquarium", "Beach", "BoatTerminal", "Bridge", "BusStation", "BusStop", "Campground", "Cemetery", "Crematorium", "EducationalOrganization", "CollegeOrUniversity", "ElementarySchool", "HighSchool", "MiddleSchool", "Preschool", "School", "EventVenue", "FireStation", "GovernmentBuilding", "CityHall", "Courthouse", "DefenceEstablishment", "Embassy", "LegislativeBuilding", "Hospital", "MovieTheater", "Museum", "MusicVenue", "Park", "ParkingFacility", "PerformingArtsTheater", "PlaceOfWorship", "BuddhistTemple", "Church", "HinduTemple", "Mosque", "Synagogue", "Playground", "PoliceStation", "PublicToilet", "RVPark", "StadiumOrArena", "SubwayStation", "TaxiStand", "TrainStation", "Zoo", "Landform", "BodyOfWater", "Canal", "LakeBodyOfWater", "OceanBodyOfWater", "Pond", "Reservoir", "RiverBodyOfWater", "SeaBodyOfWater", "Waterfall", "Continent", "Mountain", "Volcano", "LandmarksOrHistoricalBuildings", "LocalBusiness", "AnimalShelter", "ArchiveOrganization", "AutomotiveBusiness", "AutoBodyShop", "AutoDealer", "AutoPartsStore", "AutoRental", "AutoRepair", "AutoWash", "GasStation", "MotorcycleDealer", "MotorcycleRepair", "ChildCare", "Dentist", "DryCleaningOrLaundry", "EmergencyService", "FireStation", "Hospital", "PoliceStation", "EmploymentAgency", "EntertainmentBusiness", "AdultEntertainment", "AmusementPark", "ArtGallery", "Casino", "ComedyClub", "MovieTheater", "NightClub", "FinancialService", "AccountingService", "AutomatedTeller", "BankOrCreditUnion", "InsuranceAgency", "FoodEstablishment", "Bakery", "BarOrPub", "Brewery", "CafeOrCoffeeShop", "Distillery", "FastFoodRestaurant", "IceCreamShop", "Restaurant", "Winery", "GovernmentOffice", "PostOffice", "HealthAndBeautyBusiness", "BeautySalon", "DaySpa", "HairSalon", "HealthClub", "NailSalon", "TattooParlor", "HomeAndConstructionBusiness", "Electrician", "GeneralContractor", "HVACBusiness", "HousePainter", "Locksmith", "MovingCompany", "Plumber", "RoofingConstructor", "InternetCafe", "LegalService", "Attorney", "Notary", "Library", "LodgingBusiness", "BedAndBreakfast", "Campground", "Hostel", "Hotel", "Motel", "Resort", "SkiResort", "MedicalBusiness", "CommunityHealth", "Dentist", "Dermatology", "DietNutrition", "Emergency", "Geriatric", "Gynecologic", "MedicalClinic", "CovidTestingFacility", "Midwifery", "Nursing", "Obstetric", "Oncologic", "Optician", "Optometric", "Otolaryngologic", "Pediatric", "Pharmacy", "Physician", "PlasticSurgery", "Podiatric", "PrimaryCare", "Psychiatric", "PublicHealth", "ProfessionalService", "RadioStation", "RealEstateAgent", "RecyclingCenter", "SelfStorage", "ShoppingCenter", "SportsActivityLocation", "BowlingAlley", "ExerciseGym", "GolfCourse", "HealthClub", "PublicSwimmingPool", "SkiResort", "SportsClub", "StadiumOrArena", "TennisComplex", "Store", "AutoPartsStore", "BikeStore", "BookStore", "ClothingStore", "ComputerStore", "ConvenienceStore", "DepartmentStore", "ElectronicsStore", "Florist", "FurnitureStore", "GardenStore", "GroceryStore", "HardwareStore", "HobbyShop", "HomeGoodsStore", "JewelryStore", "LiquorStore", "MensClothingStore", "MobilePhoneStore", "MovieRentalStore", "MusicStore", "OfficeEquipmentStore", "OutletStore", "PawnShop", "PetStore", "ShoeStore", "SportingGoodsStore", "TireShop", "ToyStore", "WholesaleStore", "TelevisionStation", "TouristInformationCenter", "TravelAgency", "Residence", "ApartmentComplex", "GatedResidenceCommunity", "TouristAttraction", "TouristDestination", "Product", "DietarySupplment", "Drug", "IndividualProduct", "ProductCollection", "ProductGroup", "ProductModel", "SomeProducts", "Vehicle", "BusOrCoach", "Car", "Motorcycle", "MotorizedBicycle", "Taxon"];
const schemaDescriptions = new Array(schemas.length).fill(null);

while (document.childNodes.length)
document.removeChild(document.childNodes.item(0));

void function schemaForeach(index) {
  if (index === schemas.length)
  return;

  /* ... */
  var frame     = document.createElement("iframe");
  var request   = new XMLHttpRequest;
  var source    = undefined;
  var timer     = setTimeout(function() { console.log("[...]: Scraping taking longer than expected") }, 10000);
  var url       = "https://schema.org/" + schemas[index];

  /* ... */
  function schemaDocumentReadyStateChange() {
    if (null !== frame.contentWindow)
    try {
      return void frame.contentWindow.document.readyState !== "complete"
        ? setTimeout(schemaDocumentReadyStateChange)
        : schemaRequestReadyStateChange(frame.contentWindow.document)
    } catch (error) { /* --> SecurityError */ }

    schemaRequestReadyStateChange(null)
  }

  function schemaNext() {
    console.log((index + 1) + " of " + schemas.length, schemas[index], schemaDescriptions[index]);

    /* ... */
    if (null !== frame.contentWindow) {
      frame.contentWindow.close();
      frame.src = ""
    }

    document.removeChild(frame);
    request.abort();

    // ...
    clearTimeout(timer);
    schemaForeach(++index)
  }

  function schemaRequestReadyStateChange(schemaDocument) {
    function schemaGetDescriptionByDocument() {
      if (null !== schemaDocument || null !== source) {
        if (null !== schemaDocument && null !== schemaDocument.documentElement && source !== schemaDocument.documentElement.outerHTML)
        try {
          schemaDocument = frame.contentWindow.document;
          return void setTimeout(schemaGetDescriptionByDocument)
        } catch (error) { schemaGetDescriptionByRequest() }

        if (null !== schemaDocument) {
          try { schemaDescriptions[index] = "" + schemaDocument.querySelector("meta[name=description]").getAttribute("content") } catch (error) {
          try { schemaDescriptions[index] = "" + schemaDocument.getElementsByClassName("description").item(0).innerText }         catch (error) {
          } }
        }

        if (null === schemaDescriptions[index])
        schemaGetDescriptionByRequest()
      }

      schemaNext()
    }

    function schemaGetDescriptionByRequest() {
      // --> <meta name="description" content="Schema.org Type: Thing - The most generic type of item." />
      // --> <div class="description">The most generic type of item.</div>
      source = source.match(/(\<div\s+(\s*[^=>]+=\s*"[^"]*"\s*|\s*[^=>]+=\s*'[^']*'\s*|\s*[^=>]+=\s*[^\s>]\s*|)*\s*class\s*=\s*("description"|'description'|description)\s*(\s*[^=>]+=\s*"[^"]*"\s*|\s*[^=>]+=\s*'[^']*'\s*|\s*[^=>]+=\s*[^\s>]\s*|)*\>[^<]*\<\/div\>|\<meta\s+(\s*[^=>]+=\s*"[^"]*"\s*|\s*[^=>]+=\s*'[^']*'\s*|\s*[^=>]+=\s*[^\s>]\s*|)*\s*name\s*=\s*("description"|'description'|description)\s*(\s*[^=>]+=\s*"[^"]*"\s*|\s*[^=>]+=\s*'[^']*'\s*|\s*[^=>]+=\s*[^\s>]\s*|)*(\/|)\>)/);
      if (null !== source && source.length) {
        source = source[0];

        if (null !== source.match(/^\<div/))
          source = source.replace(/\<div\s+(\s*[^=>]+=\s*"[^"]*"\s*|\s*[^=>]+=\s*'[^']*'\s*|\s*[^=>]+=\s*[^\s>]\s*|)*\s*class\s*=\s*("description"|'description'|description)\s*(\s*[^=>]+=\s*"[^"]*"\s*|\s*[^=>]+=\s*'[^']*'\s*|\s*[^=>]+=\s*[^\s>]\s*|)*\>/, "").slice(0, -"</div>".length).replace(/\n.*$/g, "").trim().replace(/\.$/, "").trim();

        else if (null !== source.match(/^\<meta/)) {
          source = source.match(/(content="[^"]*"|content='[^']*'|content=[^\s]+)/);
          source = null !== source ? source[0].replace(/\n.*$/g, "").replace(new RegExp("([\"']$|^content=([\"']Schema\\.org\\s+Type\\:\\s*" + schemas[index] + "\\s*([^0-z]\\s*|)|))", 'g'), "").trim().replace(/\.$/, "").trim() : null
        }

        else
          source = null;

        schemaDescriptions[index] = source
      }
    }

    // ...
    source === undefined
      ? setTimeout(function() { schemaRequestReadyStateChange(schemaDocument) })
      : schemaGetDescriptionByDocument()
  }

  // ...
  request.onreadystatechange = function onreadystatechange(event) {
    if (request.readyState !== 0x4 /* --> XMLHttpRequest.DONE */) return;
    source = 0x0 === request.status || (request.status >= 200 && request.status < 400) ? request.responseText : null
  };

  frame.allow               = "camera 'none'; display-capture 'none'; fullscreen 'none'; geolocation 'none'; microphone 'none'";
  frame.allowFullscreen     = false;
  frame.allowPaymentRequest = false;
  frame.src                 = url;
  frame.referrerPolicy      = "origin";

  // ...
  request.open("GET", url, true, null, null);
  request.send(null);

  frame.setAttribute("sandbox", "allow-forms allow-modals allow-orientation-lock allow-pointer-lock allow-popups allow-presentation allow-scripts allow-storage-access-by-user-activation");

  document.appendChild(frame);

  // ...  
  schemaDocumentReadyStateChange()
}(0)
