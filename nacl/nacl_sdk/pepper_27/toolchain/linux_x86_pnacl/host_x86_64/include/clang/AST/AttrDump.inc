  switch (A->getKind()) {
  default:
    llvm_unreachable("Unknown attribute kind!");
    break;
  case attr::AcquiredAfter: {
    const AcquiredAfterAttr *SA = cast<AcquiredAfterAttr>(A);
    for (AcquiredAfterAttr::args_iterator I = SA->args_begin(), E = SA->args_end(); I != E; ++I)
      dumpStmt(*I);
    break;
  }
  case attr::AcquiredBefore: {
    const AcquiredBeforeAttr *SA = cast<AcquiredBeforeAttr>(A);
    for (AcquiredBeforeAttr::args_iterator I = SA->args_begin(), E = SA->args_end(); I != E; ++I)
      dumpStmt(*I);
    break;
  }
  case attr::Alias: {
    const AliasAttr *SA = cast<AliasAttr>(A);
    OS << " \"" << SA->getAliasee() << "\"";
    break;
  }
  case attr::AlignMac68k: {
    break;
  }
  case attr::Aligned: {
    const AlignedAttr *SA = cast<AlignedAttr>(A);
    if (SA->getIsMSDeclSpec()) OS << " IsMSDeclSpec";
    if (SA->isAlignmentExpr())
      dumpStmt(SA->getAlignmentExpr());
    else
      dumpType(SA->getAlignmentType()->getType());
    break;
  }
  case attr::AllocSize: {
    const AllocSizeAttr *SA = cast<AllocSizeAttr>(A);
    for (AllocSizeAttr::args_iterator I = SA->args_begin(), E = SA->args_end(); I != E; ++I)
      OS << " " << *I;
    break;
  }
  case attr::AlwaysInline: {
    break;
  }
  case attr::AnalyzerNoReturn: {
    break;
  }
  case attr::Annotate: {
    const AnnotateAttr *SA = cast<AnnotateAttr>(A);
    OS << " \"" << SA->getAnnotation() << "\"";
    break;
  }
  case attr::ArcWeakrefUnavailable: {
    break;
  }
  case attr::ArgumentWithTypeTag: {
    const ArgumentWithTypeTagAttr *SA = cast<ArgumentWithTypeTagAttr>(A);
    OS << " " << SA->getArgumentKind()->getName();
    OS << " " << SA->getArgumentIdx();
    OS << " " << SA->getTypeTagIdx();
    if (SA->getIsPointer()) OS << " IsPointer";
    break;
  }
  case attr::AsmLabel: {
    const AsmLabelAttr *SA = cast<AsmLabelAttr>(A);
    OS << " \"" << SA->getLabel() << "\"";
    break;
  }
  case attr::Availability: {
    const AvailabilityAttr *SA = cast<AvailabilityAttr>(A);
    OS << " " << SA->getPlatform()->getName();
    OS << " " << SA->getIntroduced();
    OS << " " << SA->getDeprecated();
    OS << " " << SA->getObsoleted();
    if (SA->getUnavailable()) OS << " Unavailable";
    OS << " \"" << SA->getMessage() << "\"";
    break;
  }
  case attr::Blocks: {
    const BlocksAttr *SA = cast<BlocksAttr>(A);
    switch(SA->getType()) {
    case BlocksAttr::ByRef:
      OS << " ByRef";
      break;
    }
    break;
  }
  case attr::CDecl: {
    break;
  }
  case attr::CFAuditedTransfer: {
    break;
  }
  case attr::CFConsumed: {
    break;
  }
  case attr::CFReturnsNotRetained: {
    break;
  }
  case attr::CFReturnsRetained: {
    break;
  }
  case attr::CFUnknownTransfer: {
    break;
  }
  case attr::CUDAConstant: {
    break;
  }
  case attr::CUDADevice: {
    break;
  }
  case attr::CUDAGlobal: {
    break;
  }
  case attr::CUDAHost: {
    break;
  }
  case attr::CUDALaunchBounds: {
    const CUDALaunchBoundsAttr *SA = cast<CUDALaunchBoundsAttr>(A);
    OS << " " << SA->getMaxThreads();
    OS << " " << SA->getMinBlocks();
    break;
  }
  case attr::CUDAShared: {
    break;
  }
  case attr::CarriesDependency: {
    break;
  }
  case attr::Cleanup: {
    const CleanupAttr *SA = cast<CleanupAttr>(A);
    OS << " ";
    dumpBareDeclRef(SA->getFunctionDecl());
    break;
  }
  case attr::Cold: {
    break;
  }
  case attr::Common: {
    break;
  }
  case attr::Const: {
    break;
  }
  case attr::Constructor: {
    const ConstructorAttr *SA = cast<ConstructorAttr>(A);
    OS << " " << SA->getPriority();
    break;
  }
  case attr::DLLExport: {
    break;
  }
  case attr::DLLImport: {
    break;
  }
  case attr::Deprecated: {
    const DeprecatedAttr *SA = cast<DeprecatedAttr>(A);
    OS << " \"" << SA->getMessage() << "\"";
    break;
  }
  case attr::Destructor: {
    const DestructorAttr *SA = cast<DestructorAttr>(A);
    OS << " " << SA->getPriority();
    break;
  }
  case attr::ExclusiveLockFunction: {
    const ExclusiveLockFunctionAttr *SA = cast<ExclusiveLockFunctionAttr>(A);
    for (ExclusiveLockFunctionAttr::args_iterator I = SA->args_begin(), E = SA->args_end(); I != E; ++I)
      dumpStmt(*I);
    break;
  }
  case attr::ExclusiveLocksRequired: {
    const ExclusiveLocksRequiredAttr *SA = cast<ExclusiveLocksRequiredAttr>(A);
    for (ExclusiveLocksRequiredAttr::args_iterator I = SA->args_begin(), E = SA->args_end(); I != E; ++I)
      dumpStmt(*I);
    break;
  }
  case attr::ExclusiveTrylockFunction: {
    const ExclusiveTrylockFunctionAttr *SA = cast<ExclusiveTrylockFunctionAttr>(A);
    dumpStmt(SA->getSuccessValue());
    for (ExclusiveTrylockFunctionAttr::args_iterator I = SA->args_begin(), E = SA->args_end(); I != E; ++I)
      dumpStmt(*I);
    break;
  }
  case attr::FallThrough: {
    break;
  }
  case attr::FastCall: {
    break;
  }
  case attr::Final: {
    break;
  }
  case attr::ForceInline: {
    break;
  }
  case attr::Format: {
    const FormatAttr *SA = cast<FormatAttr>(A);
    OS << " \"" << SA->getType() << "\"";
    OS << " " << SA->getFormatIdx();
    OS << " " << SA->getFirstArg();
    break;
  }
  case attr::FormatArg: {
    const FormatArgAttr *SA = cast<FormatArgAttr>(A);
    OS << " " << SA->getFormatIdx();
    break;
  }
  case attr::GNUInline: {
    break;
  }
  case attr::GuardedBy: {
    const GuardedByAttr *SA = cast<GuardedByAttr>(A);
    dumpStmt(SA->getArg());
    break;
  }
  case attr::GuardedVar: {
    break;
  }
  case attr::Hot: {
    break;
  }
  case attr::IBAction: {
    break;
  }
  case attr::IBOutlet: {
    break;
  }
  case attr::IBOutletCollection: {
    const IBOutletCollectionAttr *SA = cast<IBOutletCollectionAttr>(A);
    OS << " " << SA->getInterface().getAsString();
    OS << " ";
    SA->getInterfaceLoc().print(OS, *SM);
    break;
  }
  case attr::InitPriority: {
    const InitPriorityAttr *SA = cast<InitPriorityAttr>(A);
    OS << " " << SA->getPriority();
    break;
  }
  case attr::IntelOclBicc: {
    break;
  }
  case attr::LockReturned: {
    const LockReturnedAttr *SA = cast<LockReturnedAttr>(A);
    dumpStmt(SA->getArg());
    break;
  }
  case attr::Lockable: {
    break;
  }
  case attr::LocksExcluded: {
    const LocksExcludedAttr *SA = cast<LocksExcludedAttr>(A);
    for (LocksExcludedAttr::args_iterator I = SA->args_begin(), E = SA->args_end(); I != E; ++I)
      dumpStmt(*I);
    break;
  }
  case attr::MBlazeInterruptHandler: {
    break;
  }
  case attr::MBlazeSaveVolatiles: {
    break;
  }
  case attr::MSP430Interrupt: {
    const MSP430InterruptAttr *SA = cast<MSP430InterruptAttr>(A);
    OS << " " << SA->getNumber();
    break;
  }
  case attr::Malloc: {
    break;
  }
  case attr::MaxFieldAlignment: {
    const MaxFieldAlignmentAttr *SA = cast<MaxFieldAlignmentAttr>(A);
    OS << " " << SA->getAlignment();
    break;
  }
  case attr::MayAlias: {
    break;
  }
  case attr::MinSize: {
    break;
  }
  case attr::MsStruct: {
    break;
  }
  case attr::MultipleInheritance: {
    break;
  }
  case attr::NSBridged: {
    const NSBridgedAttr *SA = cast<NSBridgedAttr>(A);
    OS << " " << SA->getBridgedType()->getName();
    break;
  }
  case attr::NSConsumed: {
    break;
  }
  case attr::NSConsumesSelf: {
    break;
  }
  case attr::NSReturnsAutoreleased: {
    break;
  }
  case attr::NSReturnsNotRetained: {
    break;
  }
  case attr::NSReturnsRetained: {
    break;
  }
  case attr::Naked: {
    break;
  }
  case attr::NoAddressSafetyAnalysis: {
    break;
  }
  case attr::NoCommon: {
    break;
  }
  case attr::NoDebug: {
    break;
  }
  case attr::NoInline: {
    break;
  }
  case attr::NoInstrumentFunction: {
    break;
  }
  case attr::NoReturn: {
    break;
  }
  case attr::NoThreadSafetyAnalysis: {
    break;
  }
  case attr::NoThrow: {
    break;
  }
  case attr::NonNull: {
    const NonNullAttr *SA = cast<NonNullAttr>(A);
    for (NonNullAttr::args_iterator I = SA->args_begin(), E = SA->args_end(); I != E; ++I)
      OS << " " << *I;
    break;
  }
  case attr::ObjCException: {
    break;
  }
  case attr::ObjCMethodFamily: {
    const ObjCMethodFamilyAttr *SA = cast<ObjCMethodFamilyAttr>(A);
    switch(SA->getFamily()) {
    case ObjCMethodFamilyAttr::OMF_None:
      OS << " OMF_None";
      break;
    case ObjCMethodFamilyAttr::OMF_alloc:
      OS << " OMF_alloc";
      break;
    case ObjCMethodFamilyAttr::OMF_copy:
      OS << " OMF_copy";
      break;
    case ObjCMethodFamilyAttr::OMF_init:
      OS << " OMF_init";
      break;
    case ObjCMethodFamilyAttr::OMF_mutableCopy:
      OS << " OMF_mutableCopy";
      break;
    case ObjCMethodFamilyAttr::OMF_new:
      OS << " OMF_new";
      break;
    }
    break;
  }
  case attr::ObjCNSObject: {
    break;
  }
  case attr::ObjCPreciseLifetime: {
    break;
  }
  case attr::ObjCRequiresPropertyDefs: {
    break;
  }
  case attr::ObjCRequiresSuper: {
    break;
  }
  case attr::ObjCReturnsInnerPointer: {
    break;
  }
  case attr::ObjCRootClass: {
    break;
  }
  case attr::OpenCLKernel: {
    break;
  }
  case attr::Overloadable: {
    break;
  }
  case attr::Override: {
    break;
  }
  case attr::Ownership: {
    const OwnershipAttr *SA = cast<OwnershipAttr>(A);
    switch(SA->getOwnKind()) {
    case OwnershipAttr::Holds:
      OS << " Holds";
      break;
    case OwnershipAttr::Returns:
      OS << " Returns";
      break;
    case OwnershipAttr::Takes:
      OS << " Takes";
      break;
    }
    OS << " \"" << SA->getModule() << "\"";
    for (OwnershipAttr::args_iterator I = SA->args_begin(), E = SA->args_end(); I != E; ++I)
      OS << " " << *I;
    break;
  }
  case attr::Packed: {
    break;
  }
  case attr::Pascal: {
    break;
  }
  case attr::Pcs: {
    const PcsAttr *SA = cast<PcsAttr>(A);
    switch(SA->getPCS()) {
    case PcsAttr::AAPCS:
      OS << " AAPCS";
      break;
    case PcsAttr::AAPCS_VFP:
      OS << " AAPCS_VFP";
      break;
    }
    break;
  }
  case attr::PnaclCall: {
    break;
  }
  case attr::PtGuardedBy: {
    const PtGuardedByAttr *SA = cast<PtGuardedByAttr>(A);
    dumpStmt(SA->getArg());
    break;
  }
  case attr::PtGuardedVar: {
    break;
  }
  case attr::Ptr32: {
    break;
  }
  case attr::Ptr64: {
    break;
  }
  case attr::Pure: {
    break;
  }
  case attr::Regparm: {
    const RegparmAttr *SA = cast<RegparmAttr>(A);
    OS << " " << SA->getNumParams();
    break;
  }
  case attr::ReqdWorkGroupSize: {
    const ReqdWorkGroupSizeAttr *SA = cast<ReqdWorkGroupSizeAttr>(A);
    OS << " " << SA->getXDim();
    OS << " " << SA->getYDim();
    OS << " " << SA->getZDim();
    break;
  }
  case attr::ReturnsTwice: {
    break;
  }
  case attr::ScopedLockable: {
    break;
  }
  case attr::Section: {
    const SectionAttr *SA = cast<SectionAttr>(A);
    OS << " \"" << SA->getName() << "\"";
    break;
  }
  case attr::Sentinel: {
    const SentinelAttr *SA = cast<SentinelAttr>(A);
    OS << " " << SA->getSentinel();
    OS << " " << SA->getNullPos();
    break;
  }
  case attr::SharedLockFunction: {
    const SharedLockFunctionAttr *SA = cast<SharedLockFunctionAttr>(A);
    for (SharedLockFunctionAttr::args_iterator I = SA->args_begin(), E = SA->args_end(); I != E; ++I)
      dumpStmt(*I);
    break;
  }
  case attr::SharedLocksRequired: {
    const SharedLocksRequiredAttr *SA = cast<SharedLocksRequiredAttr>(A);
    for (SharedLocksRequiredAttr::args_iterator I = SA->args_begin(), E = SA->args_end(); I != E; ++I)
      dumpStmt(*I);
    break;
  }
  case attr::SharedTrylockFunction: {
    const SharedTrylockFunctionAttr *SA = cast<SharedTrylockFunctionAttr>(A);
    dumpStmt(SA->getSuccessValue());
    for (SharedTrylockFunctionAttr::args_iterator I = SA->args_begin(), E = SA->args_end(); I != E; ++I)
      dumpStmt(*I);
    break;
  }
  case attr::SingleInheritance: {
    break;
  }
  case attr::StdCall: {
    break;
  }
  case attr::TLSModel: {
    const TLSModelAttr *SA = cast<TLSModelAttr>(A);
    OS << " \"" << SA->getModel() << "\"";
    break;
  }
  case attr::ThisCall: {
    break;
  }
  case attr::TransparentUnion: {
    break;
  }
  case attr::TypeTagForDatatype: {
    const TypeTagForDatatypeAttr *SA = cast<TypeTagForDatatypeAttr>(A);
    OS << " " << SA->getArgumentKind()->getName();
    OS << " " << SA->getMatchingCType().getAsString();
    if (SA->getLayoutCompatible()) OS << " LayoutCompatible";
    if (SA->getMustBeNull()) OS << " MustBeNull";
    break;
  }
  case attr::Unavailable: {
    const UnavailableAttr *SA = cast<UnavailableAttr>(A);
    OS << " \"" << SA->getMessage() << "\"";
    break;
  }
  case attr::UnlockFunction: {
    const UnlockFunctionAttr *SA = cast<UnlockFunctionAttr>(A);
    for (UnlockFunctionAttr::args_iterator I = SA->args_begin(), E = SA->args_end(); I != E; ++I)
      dumpStmt(*I);
    break;
  }
  case attr::Unused: {
    break;
  }
  case attr::Used: {
    break;
  }
  case attr::Uuid: {
    const UuidAttr *SA = cast<UuidAttr>(A);
    OS << " \"" << SA->getGuid() << "\"";
    break;
  }
  case attr::VecReturn: {
    break;
  }
  case attr::VirtualInheritance: {
    break;
  }
  case attr::Visibility: {
    const VisibilityAttr *SA = cast<VisibilityAttr>(A);
    switch(SA->getVisibility()) {
    case VisibilityAttr::Default:
      OS << " Default";
      break;
    case VisibilityAttr::Hidden:
      OS << " Hidden";
      break;
    case VisibilityAttr::Protected:
      OS << " Protected";
      break;
    }
    break;
  }
  case attr::WarnUnusedResult: {
    break;
  }
  case attr::Weak: {
    break;
  }
  case attr::WeakImport: {
    break;
  }
  case attr::WeakRef: {
    break;
  }
  case attr::Win64: {
    break;
  }
  case attr::WorkGroupSizeHint: {
    const WorkGroupSizeHintAttr *SA = cast<WorkGroupSizeHintAttr>(A);
    OS << " " << SA->getXDim();
    OS << " " << SA->getYDim();
    OS << " " << SA->getZDim();
    break;
  }
  case attr::X86ForceAlignArgPointer: {
    break;
  }
  }
